#include <iostream>
#include <opencv2/opencv.hpp>
#include "Target.hpp"

Target::Target(std::vector<cv::Point> contour) {
  m_contour = contour;
}
double Target::maxX() {
  double max = m_contour[1].x;
  for (unsigned int i = 0; i < m_contour.size(); i++) {
      if (m_contour[i].x > max) {
        max = m_contour[i].x;
      }
  }
  std::cout << "Max X " << max << "\n";
  return max;
}
double Target::minX() {
  double min = m_contour[1].x;
  for (unsigned int i = 0; i < m_contour.size(); i++) {
    if (m_contour[i].x < min) {
      min = m_contour[i].x;
    }
  }
  std::cout << "Min X " << min << "\n";
  return min;
}
double Target::maxY() {
  double max = m_contour[1].y;;
  for (unsigned int i = 0; i < m_contour.size(); i++) {
      if (m_contour[i].y > max) {
        max = m_contour[i].y;
      }
  }
  std::cout << "Max Y " << max << "\n";
  return max;
}
double Target::minY(){
  double min;
  min = m_contour[1].y;
  for (unsigned int i = 0; i < m_contour.size(); i++) {
    if (m_contour[i].y < min) {
      min = m_contour[i].y;
    }
  }
  std::cout << "Min Y " << min << "\n";
  return min;
}

double Target::findWidth() {
  return (maxX() - minX());
}
double Target::findHeight() {
  return (maxY() - minY());
}
double Target::findCenterX() {
  return ((maxX() + minX())/2);
}
double Target::findCenterY() {
  return ((maxY() + minY())/2);
}
