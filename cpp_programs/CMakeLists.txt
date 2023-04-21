project(metavision_sdk_get_started)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(MetavisionSDK_DIR ~/Downloads/openeb/build/generated/share/cmake/MetavisionSDKCMakePackagesFilesDir)
set(MetavisionHAL_DIR ~/Downloads/openeb/build/generated/share/cmake/MetavisionHALCMakePackagesFilesDir)

find_package(MetavisionSDK COMPONENTS core driver ui REQUIRED)
find_package(OpenCV COMPONENTS highgui REQUIRED)
#find_package(Boost COMPONENTS program_options REQUIRED)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#TARGET_LINK_LIBRARIES(target ${Boost_LIBRARIES})


set (sample metavision_sdk_get_started)
add_executable(${sample} ${sample}.cpp)
target_link_libraries(${sample} MetavisionSDK::core MetavisionSDK::driver MetavisionSDK::ui opencv_highgui)

set (sample pipeline_test)
add_executable(${sample} ${sample}.cpp)
target_link_libraries(${sample} MetavisionSDK::core MetavisionSDK::driver MetavisionSDK::ui opencv_highgui)

set (sample pipeline_final)
add_executable(${sample} ${sample}.cpp)
target_link_libraries(${sample} MetavisionSDK::core MetavisionSDK::driver MetavisionSDK::ui opencv_highgui)
