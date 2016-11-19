#include <iostream>
#include "TargetProcessor.hpp"
#include "Target.hpp"

TargetProcessor::TargetProcessor(double realWidth, double focalLength, double imageWidth, double imageHeight) {
  m_realWidth = realWidth;
  m_focalLength = focalLength;
  m_imageWidth = imageWidth;
  m_imageHeight = imageHeight;
}

void TargetProcessor::loadTarget(Target *target) {
  width = target->findWidth();
  height = target->findHeight();
  centerX = target->findCenterX();
  centerY = target->findCenterY();
}

double TargetProcessor::calcDistance() {
  double distance = (m_focalLength * m_realWidth)/width;

  return distance;
}

double TargetProcessor::calcAzimuthX() {
  double cent2cent = (m_imageWidth/2) - centerX;
  double distance = calcDistance();
  double angleX = atan(cent2cent/distance) * 180 / 3.14159;

  return angleX;
}

double TargetProcessor::calcAzimuthY() {
    double cent2cent = (m_imageHeight/2) - centerY;
    double distance = calcDistance();
    double angleY = atan(cent2cent/distance) * 180 / 3.14159;

    return angleY;
}
