#include <opencv2/opencv.hpp>
#include <iostream>
#include "TargetDetector.hpp"
using namespace cv;

TargetDetector::TargetDetector(cv::Mat img) {
  m_img = img;
}

std::vector<Point> TargetDetector::getTarget() {
  Mat img_hsv;
  cvtColor(m_img, img_hsv, CV_BGR2HSV);
  std::vector<cv::Mat> channels;
  split(img_hsv, channels);

  Mat hueOrig = channels.at(0).clone();
  Mat threshLower, threshUpper;
  Mat result;

  threshold(hueOrig, threshLower, 50, 255, CV_THRESH_BINARY);
  threshold(hueOrig, threshUpper, 300, 255, CV_THRESH_BINARY_INV);

  result = threshLower & threshUpper;



  Mat edges;
  std::vector<std::vector<Point> > contours;

  Canny(result, edges, 0, 25, 3, false);

  cv::findContours(edges, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  std::vector<Point> approxContour;

  for(int i = 0; i < contours.size(); i++) {

    approxPolyDP(contours[i], approxContour, cv::arcLength(cv::Mat(contours.at(i)), true) * 0.02, true);

    if (approxContour.size() == 4 && contours[i][1].y >= 240) {
      std::cout << "contour" << contours[i][1].y << "\n";
      break;
    }

  }

  return approxContour;
}
