#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
// #include "Target.cpp"
// #include "TargetProcessor.cpp"
// #include "TargetDetector.cpp"
#include "Target.hpp"
#include "TargetProcessor.hpp"
#include "TargetDetector.hpp"

int main(int argc, char* argv[]) {
  std::string fileLocation = argv[1];
  Mat img_rgb = imread(fileLocation);
  TargetDetector otd(img_rgb);
  Target ot(otd.getTarget());
  Target *target = &ot;
  TargetProcessor otp(400);

  otp.loadTarget(target);

  std::cout << "Distance: " << otp.calcDistance() << "\n";
  std::cout << "Azimuth X: " << otp.calcAzimuthX() << "\n";
  std::cout << "Azimuth Y: " << otp.calcAzimuthY() << "\n";

  return 0;
}
