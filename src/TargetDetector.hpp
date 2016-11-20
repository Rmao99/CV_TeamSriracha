#ifndef TARGETDETECTOR_HPP
#define TARGETDETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

class TargetDetector
{
public:
  TargetDetector();
  std::vector<cv::Point> getTarget(cv::Mat img, int corners);
private:
  cv::Mat m_img;
};

#endif
