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
    string ans;
    bool has_ROI;
    bool has_polarity;
    int ROI_coord[4] = {0, 0, 0, 0}; // coordinates for ROI filter - will be changed later
    // Collecting user choices
    cout << "Welcome to the pipeline \n";
    cout << "Available keyboard options:\n"
                                                             "  - r - toggle the ROI filter algorithm\n"
                                                             "  - p - show only events of positive polarity\n"
                                                             "  - n - show only events of negative polarity\n"
                                                             "  - a - show all events\n"
                                                             "  - s - set parameter for ROI filter\n"
                                                             "  - q - quit the application\n";

    cout << "Do you want to implement a ROI filter algorithmn ? (Y/N)";
    cin >> ans;
    if (ans == "Y" || ans == "y")
    {
        has_ROI = true;
        cout << "Define X coordinate of bottom left corner";
        cin >> ROI_coord[0];
        cout << "Define Y coordinate of bottom left corner";
        cin >> ROI_coord[1];
        cout << "Define X coordinate of top right corner";
        cin >> ROI_coord[2];
        cout << "Define Y coordinate of top right corner";
        cin >> ROI_coord[3];
    }
    else
    {
        has_ROI = false;
    }
    cout << "Do you want to implement a polarity filter algorithmn ? (Y/N)";
    cin >> ans;
    if (ans == "Y" || ans == "y")
    {
        has_polarity = true;
    }
    else
    {
        has_polarity = false;
    }
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
    const uint32_t accumulation_time_ms                  = 6;
    const int display_fps                                = 80;

    // Creating a linear pipeline with all the filters and parameters
    auto &cam_stage = p.add_stage(std::make_unique<Metavision::CameraStage>(std::move(cam), event_buffer_duration_ms));
    auto &pol_filter_stage = p.add_algorithm_stage(std::make_unique<Metavision::PolarityFilterAlgorithm>(1), cam_stage, false);
    auto &roi_stage = p.add_algorithm_stage(std::make_unique<Metavision::RoiFilterAlgorithm>(ROI_coord[0], ROI_coord[1], ROI_coord[2], ROI_coord[3], false), pol_filter_stage, false);
    auto &frame_generation_stage = p.add_stage(std::make_unique<Metavision::FrameGenerationStage>(width, height, accumulation_time_ms), roi_stage);

    // Removing unnecessary filters following user choices
    if (!has_polarity)
    {
        p.remove_stage(pol_filter_stage);

        if(!has_ROI)
        {
            p.remove_stage(roi_stage);
            frame_generation_stage.set_previous_stage(cam_stage);
        }
        else
        {
            roi_stage.set_previous_stage(cam_stage);
            frame_generation_stage.set_previous_stage(roi_stage);
        }
    }

    // Creating the display stage
    auto &frame_disp_stage= p.add_stage(
        std::make_unique<Metavision::FrameDisplayStage>("Final Stage", width, height),
        frame_generation_stage);

    // Keyboard callbacks
    frame_disp_stage.set_key_callback([&](Metavision::UIKeyEvent key, int scancode, Metavision::UIAction action, int mods) {
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
                roi_stage.set_enabled(!roi_stage.is_enabled());
                break;
            }
        }

    });
    // Run the pipeline and wait for its completion
    p.run();

    return 0;
}
