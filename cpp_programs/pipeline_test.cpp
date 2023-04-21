//#define BOOST_TEST_MODULE subcommand options

//#include <boost/program_options.hpp>

#include <iostream>
#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/base/events/event_cd.h>
#include <metavision/sdk/core/algorithms/roi_filter_algorithm.h>
#include <metavision/sdk/core/algorithms/polarity_filter_algorithm.h>
#include <metavision/sdk/core/algorithms/polarity_filter_algorithm.h>
#include <metavision/sdk/ui/utils/window.h>
#include <metavision/sdk/ui/utils/event_loop.h>
#include <metavision/sdk/core/pipeline/pipeline.h>
#include <metavision/sdk/core/pipeline/frame_generation_stage.h>
#include <metavision/sdk/ui/pipeline/frame_display_stage.h>
#include <metavision/sdk/core/pipeline/frame_composition_stage.h>
#include <metavision/sdk/driver/pipeline/camera_stage.h>
#include <metavision/sdk/base/utils/timestamp.h>
#include <metavision/sdk/driver/antiflicker_module.h>


int main(int argc, char *argv[]) {

    using namespace std;
    string in_raw_file_path;
    short ROI_param = 80;
    cout << "Welcome to the pipeline \n";
    cout << "Available keyboard options:\n"
                                                             "  - r - toggle the ROI filter algorithm\n"
                                                             "  - p - show only events of positive polarity\n"
                                                             "  - n - show only events of negative polarity\n"
                                                             "  - a - show all events\n"
                                                             "  - s - set parameter for ROI filter\n"
                                                             "  - q - quit the application\n";
    /*
    const std::string short_program_desc("Code sample showing how the pipeline utility can be used to "
                                         "create a simple application to filter and display events.\n");

    const std::string long_program_desc(short_program_desc + "Available keyboard options:\n"
                                                             "  - r - toggle the ROI filter algorithm\n"
                                                             "  - p - show only events of positive polarity\n"
                                                             "  - n - show only events of negative polarity\n"
                                                             "  - a - show all events\n"
                                                             "  - q - quit the application\n");
    namespace po = boost::program_options;
    po::options_description options_desc("Options");
    // clang-format off
    options_desc.add_options()
        ("help,h", "Produce help message.")
        ("input-raw-file,i", po::value<std::string>(&in_raw_file_path), "Path to input RAW file. If not specified, the camera live stream is used.")
        ;
    // clang-format on

    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(options_desc).run(), vm);
        po::notify(vm);
    } catch (po::error &e) {
        MV_LOG_ERROR() << short_program_desc;
        MV_LOG_ERROR() << options_desc;
        MV_LOG_ERROR() << "Parsing error:" << e.what();
        return 1;
    }

    if (vm.count("help")) {
        MV_LOG_INFO() << short_program_desc;
        MV_LOG_INFO() << options_desc;
        return 0;
    }

    MV_LOG_INFO() << long_program_desc;
    */
    // A pipeline for which all added stages will automatically be run in their own processing threads (if applicable)
    Metavision::Pipeline p(true);

    // Construct a camera from a recording or a live stream
    Metavision::Camera cam;
    if (!in_raw_file_path.empty()) {
        cam = Metavision::Camera::from_file(in_raw_file_path);
    } else {
        cam = Metavision::Camera::from_first_available();
    }
    const unsigned short width  = cam.geometry().width();
    const unsigned short height = cam.geometry().height();

    const Metavision::timestamp event_buffer_duration_ms = 2;
    const uint32_t accumulation_time_ms                  = 10;
    const int display_fps                                = 100;

    /// Pipeline
    //
    //  0 (Camera) ---------------->---------------- 1 (Polarity Filter)
    //  |                                            |
    //  v                                            v
    //  |                                            |
    //  2 (Frame Generation)                         3 (Frame Generation)
    //  |                                            |
    //  v                                            v
    //  |------>-----  4 (Frame Composer)  ----<-----|
    //                 |
    //                 v
    //                 |
    //                 5 (Display)
    //

    // 0) Stage producing events from a camera
    auto &cam_stage = p.add_stage(std::make_unique<Metavision::CameraStage>(std::move(cam), event_buffer_duration_ms));

    // 1) Camera -> Polarity filter
    auto &pol_filter_stage = p.add_algorithm_stage(std::make_unique<Metavision::PolarityFilterAlgorithm>(1), cam_stage, false);

    // 2) Polarity_filter -> FrameGeneration
    auto &left_frame_stage =
        p.add_stage(std::make_unique<Metavision::FrameGenerationStage>(width, height, accumulation_time_ms), pol_filter_stage);

    // 3) Polarity_filter -> Roi_filter
    auto &roi_filter_stage = p.add_algorithm_stage(
        std::make_unique<Metavision::RoiFilterAlgorithm>(140, 140, width - 140, height - 140, false), pol_filter_stage, false);

    // 4) Roi_filter -> FrameGeneration
    auto &right_frame_stage = p.add_stage(
        std::make_unique<Metavision::FrameGenerationStage>(width, height, accumulation_time_ms), roi_filter_stage);

    /*
    // 4) Stage generating a combined frame
    auto &full_frame_stage = p.add_stage(std::make_unique<Metavision::FrameCompositionStage>(display_fps));
    full_frame_stage.add_previous_frame_stage(left_frame_stage, 0, 0, width, height);
    full_frame_stage.add_previous_frame_stage(right_frame_stage, width + 10, 0, width, height);
    */

    // 5) Stage displaying the frame without ROI
    /*const auto full_width  = full_frame_stage.frame_composer().get_total_width();
    const auto full_height = full_frame_stage.frame_composer().get_total_height();*/
    auto &disp_left_stage       = p.add_stage(
        std::make_unique<Metavision::FrameDisplayStage>("Left Stage (without ROI applicable)", width, height),
        left_frame_stage);
    auto &disp_right_stage       = p.add_stage(
        std::make_unique<Metavision::FrameDisplayStage>("Right Stage (with ROI applicable)", width-280, height-280),
        right_frame_stage);

    disp_right_stage.set_key_callback([&](Metavision::UIKeyEvent key, int scancode, Metavision::UIAction action, int mods) {
        if (action == Metavision::UIAction::RELEASE) {
            switch (key) {
            case Metavision::UIKeyEvent::KEY_A:
                // show all events
                pol_filter_stage.set_enabled(false);
                break;
            case Metavision::UIKeyEvent::KEY_N:
                // show only negative events
                pol_filter_stage.set_enabled(true);
                pol_filter_stage.algo().set_polarity(0);
                break;
            case Metavision::UIKeyEvent::KEY_P:
                // show only positive events
                pol_filter_stage.set_enabled(true);
                pol_filter_stage.algo().set_polarity(1);
                break;
            case Metavision::UIKeyEvent::KEY_R:
                // toggle ROI filter
                roi_filter_stage.set_enabled(!roi_filter_stage.is_enabled());
                break;
            }
        }

    });
    // Run the pipeline and wait for its completion
    p.run();

    return 0;
}
