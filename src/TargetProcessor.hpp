#ifndef TARGET_PROCESSOR_H
#define TARGET_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "Target.hpp"

class TargetProcessor
{
public:
  TargetProcessor(double focalLength=415.0);
  void loadTarget(Target *target, double realWidth, cv::Mat img);
  double calcDistance();
  double calcAzimuthX();
  double calcAzimuthY();

private:
  double m_focalLength;
  double m_realWidth;
  double m_picWidth;
  double m_picHeight;
  double width;
  double height;
  double centerX;
  double centerY;
};

#endif
