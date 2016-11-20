#ifndef TARGET_PROCESSOR_H
#define TARGET_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "Target.hpp"

class TargetProcessor
{
public:
  TargetProcessor(double focalLength=1.5, double imageWidth=480.0, double imageHeight=240.0);
  void loadTarget(Target *target, double realWidth);
  double calcDistance();
  double calcAzimuthX();
  double calcAzimuthY();

private:
  double m_focalLength;
  double m_imageWidth;
  double m_realWidth;
  double m_imageHeight;
  double width;
  double height;
  double centerX;
  double centerY;
};

#endif
