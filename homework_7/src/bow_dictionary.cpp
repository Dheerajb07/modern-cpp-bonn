#include "bow_dictionary.hpp"

using ipb::BowDictionary;

static BowDictionary &GetInstance() {
  static BowDictionary instance;
  return instance;
}

void set_params(const int max_iter, const int size,
                const std::vector<cv::Mat> &descriptors) {
  set_max_iterations(max_iter);
  set_size(size);
  set_descriptors(descriptors);
}

int total_features() const {
  int num_features = 0;
  for (const cv::Mat &mat : descriptors) {
    num_features += mat.rows;
  }
  return num_features;
}