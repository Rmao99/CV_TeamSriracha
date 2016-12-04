#ifndef TARGET_H
#define TARGET_H
#include <opencv2/opencv.hpp>

class Target
{
public:
  Target(std::vector<cv::Point> contour);
  std::vector<cv::Point> m_contour;
  double findCenterX();
  double findCenterY();
  double findWidth();
  double findHeight();

private:
  double maxX();
  double minX();
  double maxY();
  double minY();
};
#endif
