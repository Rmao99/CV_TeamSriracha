#include <opencv2/opencv.hpp>
#include <iostream>
#include "TargetDetector.hpp"
using namespace cv;

TargetDetector::TargetDetector() {

}

double TargetDetector::angle(cv::Point p1, cv::Point p2, cv::Point p0) {
  double dx1 = p1.x - p0.x;
  double dy1 = p1.y - p0.y;
  double dx2 = p2.x - p0.x;
  double dy2 = p2.y - p0.y;
  return atan(dy1/dx1)-atan(dy2/dx2);
}

std::vector<Point> TargetDetector::getTarget(cv::Mat img, int corners) {
  m_img = img;
  Mat img_hsv;
  cvtColor(m_img, img_hsv, CV_BGR2HSV);
  std::vector<cv::Mat> channels;
  split(img_hsv, channels);

  Mat hueOrig = channels.at(0).clone();
  Mat valOrig = channels.at(2).clone();
  Mat threshLower, threshUpper;
  Mat valResult;
  Mat hueResult;
  Mat result;

  threshold(hueOrig, threshLower, 0, 255, CV_THRESH_BINARY);
  threshold(hueOrig, threshUpper, 102, 255, CV_THRESH_BINARY_INV);

  hueResult = threshLower & threshUpper;

  threshold(valOrig, threshLower, 227, 255, CV_THRESH_BINARY);
  threshold(valOrig, threshUpper, 255, 255, CV_THRESH_BINARY_INV);

  valResult = threshLower & threshUpper;

  result = hueResult & valResult;

  Mat edges;
  std::vector<std::vector<Point> > contours;

  Canny(result, edges, 0, 25, 3, false);
  //imshow("result", result);
  cv::findContours(edges, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  std::vector<Point> approxContour;

  for(int i = 0; i < contours.size(); i++) {

    approxPolyDP(contours[i], approxContour, cv::arcLength(cv::Mat(contours.at(i)), true) * 0.02, true);
// 500 should be changed after testing
// 2000 should be changed after testing

    if ( ( (approxContour.size() == corners) || ( (corners == 4) && (contours[i][1].y >= 200) ) ) && (cv::contourArea(approxContour, false) > 100) ) {
      double maxCosine = 0;
      for (int j = 2; j<=4; j++) {
        double cosine;
        try {
          cosine = fabs(cos(angle(approxContour.at(j%4), approxContour.at(j-2), approxContour.at(j-1))));
        }
        catch(std::exception e) {
          std::cout << e.what();
        }
        maxCosine = MAX(maxCosine, cosine);
      }

      if(maxCosine < .2) {

      cv::drawContours(img, contours, i , Scalar(255,0,0), 5);
      std::cout << "y-coordinate of first contour: " << contours[i][1].y << "\n";
      return approxContour;
      }
    }

  }
  return std::vector<Point>();
}
