#include <iostream>
#include <opencv2/opencv.hpp>
#include "TargetProcessor.hpp"
#include "Target.hpp"


TargetProcessor::TargetProcessor(double focalLength) {
  m_focalLength = focalLength;
}

void TargetProcessor::loadTarget(Target *target, double realWidth, cv::Mat img) {
  width = target->findWidth();
  height = target->findHeight();
  centerX = target->findCenterX();
  centerY = target->findCenterY();
  m_realWidth = realWidth;
  m_picWidth = img.size().width;
  m_picHeight = img.size().height;
}

double TargetProcessor::calcDistance() {
  double distance = (m_focalLength * m_realWidth)/width;

  return distance;
}

double TargetProcessor::calcAzimuthX() {
  double distance = calcDistance();
  double cent2cent = ((centerX - (m_picWidth/2)) * distance)/m_focalLength;

  double angleX = atan(cent2cent/distance) * 180 / 3.14159;

  return angleX;
}

double TargetProcessor::calcAzimuthY() {
    double distance = calcDistance();
    double cent2cent = ((centerY - (m_picHeight/2)) * distance)/m_focalLength;
    double angleY = atan(cent2cent/distance) * 180 / 3.14159;

    return angleY;
}
