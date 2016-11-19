#ifndef TARGETDETECTOR_HPP
#define TARGETDETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

class TargetDetector
{
public:
  TargetDetector(cv::Mat img);
  std::vector<cv::Point> getTarget();
private:
  cv::Mat m_img;
};

#endif
