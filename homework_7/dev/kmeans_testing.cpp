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

cv::Mat Get18Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 3; j++) {
      data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

cv::Mat Get5Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  for (int i = 0; i < 100; i += 20) {
    cv::Mat_<float> vec(rows_num, cols_num, i);
    data.push_back(vec);
  }

  return data;
}

int main() {
  auto data = GetDummyData();
  //   std::cout << data << std::endl;

  // auto gt_cluster = Get2Kmeans();
  auto gt_cluster = Get18Kmeans();

  const int dict_size = gt_cluster.rows;
  const int iterations = 10;
  cv::Mat centroids = ipb::kMeans(data, dict_size, iterations);
  cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  std::cout << "Final Centroids : " << std::endl;
  std::cout << centroids << std::endl;

  std::cout << "Correct Centroids : " << std::endl;
  std::cout << gt_cluster << std::endl;

  return 0;
}