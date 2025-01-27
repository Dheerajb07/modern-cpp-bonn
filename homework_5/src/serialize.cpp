#include "serialize.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <string>
#include <vector>

namespace ipb::serialization {

template <class T>
void readMat(cv::Mat &matrix, T &element, std::ifstream &bin_file) {

  for (int i = 0; i < matrix.rows; i++) {

    for (int j = 0; j < matrix.cols; j++) {

      bin_file.read(reinterpret_cast<char *>(&element), sizeof(T));
      matrix.at<T>(i, j) = element;
    }
  }
}

template <class T>
void writeMat(const cv::Mat &matrix, T &element, std::ofstream &bin_file) {
  for (int i = 0; i < matrix.rows; i++) {

    for (int j = 0; j < matrix.cols; j++) {

      element = matrix.at<T>(i, j);
      bin_file.write(reinterpret_cast<char *>(&element), sizeof(T));
    }
  }
}

typedef unsigned char uint8;

void Serialize(const cv::Mat &img, const std::string &filename) {
  // open bin_file
  std::ofstream bin_file(filename, std::ios_base::out | std::ios_base::binary |
                                       std::ios_base::trunc);

  // vector to store image info
  std::vector<int> img_info = {img.rows, img.cols, img.type()};

  // write info into to the beginning of binary file
  bin_file.write(reinterpret_cast<char *>(&img_info.front()),
                 img_info.size() * sizeof(int));

  /* check mat type
     type == CV_8UC3 == 16 == RGB Image
     type == CV_32FC1 == 5  == SIFT Descriptor
     type == CV_8UC1 == 0  == GRAYSCALE IMG
  */
  if (img.type() == CV_8UC3) {

    cv::Vec3b rgb;
    writeMat(img, rgb, bin_file);

  } else if (img.type() == CV_32FC1) {

    float value;
    writeMat(img, value, bin_file);

  } else if (img.type() == CV_8UC1) {

    uint8 mono;
    writeMat(img, mono, bin_file);
  }
}

cv::Mat Deserialize(const std::string &filename) {
  // open bin_file
  std::ifstream bin_file(filename, std::ios_base::in | std::ios_base::binary);

  // read info vector
  std::vector<int> img_info = {0, 0, 0};
  bin_file.read(reinterpret_cast<char *>(&img_info.front()),
                img_info.size() * sizeof(int));

  // init mat
  cv::Mat img = cv::Mat::zeros(img_info[0], img_info[1], img_info[2]);

  /* check mat type
     type == CV_8UC3 == 16 == RGB Image
     type == CV_32FC1 == 5  == SIFT Descriptor
     type == CV_8UC1 == 0  == GRAYSCALE IMG
  */
  if (img_info[2] == CV_8UC3) {

    cv::Vec3b rgb;
    readMat(img, rgb, bin_file);

  } else if (img_info[2] == CV_32FC1) {

    float value;
    readMat(img, value, bin_file);

  } else if (img_info[2] == CV_8UC1) {

    uint8 mono;
    readMat(img, mono, bin_file);
  }

  return img;
}
} // namespace ipb::serialization