find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(CV_TeamSriracha cv-sriracha.cpp VideoDevice.cpp AppConfig.cpp CmdLineInterface.cpp TargetDetector.cpp Target.cpp TargetProcessor.cpp)
target_link_libraries(CV_TeamSriracha ${OpenCV_LIBS} ${Boost_LIBRARIES})
