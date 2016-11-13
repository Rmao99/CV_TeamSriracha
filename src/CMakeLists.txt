find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(cv_camera_test cv_camera_test.cpp VideoDevice.cpp AppConfig.cpp CmdLineInterface.cpp)
target_link_libraries(cv_camera_test ${OpenCV_LIBS} ${Boost_LIBRARIES})
