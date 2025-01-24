#include "serialize.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <string>

namespace ipb::serialization {

void Serialize(const cv::Mat &img, const std::string &filename) {
  std::ofstream bin_file(filename, std::ios_base::out | std::ios_base::binary |
                                       std::ios_base::trunc);

  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
      bin_file.write(reinterpret_cast<char *>(&pixel), sizeof(cv::Vec3b));
    }
  }
}

cv::Mat Deserialize(const std::string &filename) {
  std::ifstream bin_file(filename, std::ios_base::in | std::ios_base::binary);

  int nrows = 512;
  int ncols = 512;

  cv::Mat img = cv::Mat::zeros(nrows, ncols, CV_8UC3);
  cv::Vec3b pixel;

  for (int i = 0; i < nrows; i++) {
    for (int j = 0; j < ncols; j++) {
      bin_file.read(reinterpret_cast<char *>(&pixel), sizeof(cv::Vec3b));
      img.at<cv::Vec3b>(i, j) = pixel;
    }
  }

  return img;
}

} // namespace ipb::serialization