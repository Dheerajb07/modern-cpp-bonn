#include "homework_7.h"
#include <filesystem>
#include <iostream>
#include <opencv2/core.hpp>
#include <vector>

std::vector<cv::Mat> &GetDummyData() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  static std::vector<cv::Mat> data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 5; j++) {
      data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

cv::Mat GetAllFeatures() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 5; j++) {
      data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

cv::Mat Get2Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  data.push_back(cv::Mat_<float>(rows_num, cols_num, 20.000002F));
  data.push_back(cv::Mat_<float>(rows_num, cols_num, 70.0F));

  return data;
}

int main() {
  auto data = GetDummyData();
  //   std::cout << data << std::endl;

  // auto gt_cluster = Get2Kmeans();
  auto gt_cluster = GetAllFeatures();

  const int dict_size = gt_cluster.rows;
  const int iterations = 1;
  cv::Mat centroids = ipb::kMeans(data, dict_size, iterations);

  std::cout << "Final Centroids : " << std::endl;
  std::cout << centroids << std::endl;

  std::cout << "Correct Centroids : " << std::endl;
  std::cout << gt_cluster << std::endl;

  return 0;
}