#include "bow_dictionary.hpp"
#include "kmeans.hpp"
#include <iostream>

using namespace ipb;

// get singleton object instance
BowDictionary &BowDictionary::GetInstance() {
  static BowDictionary instance;
  return instance;
}

// Set bow_dict params
void BowDictionary::set_params(const int max_iter, const int size,
                               const std::vector<cv::Mat> &descriptors) {
  // set params
  max_iter_ = max_iter;
  dict_size_ = size;
  descriptors_ = descriptors;

  // create vocabulary using the above params
  BowDictionary::update_vocabulary();
}

// update vocabulary
void BowDictionary::update_vocabulary() {
  if (!descriptors_.empty() && max_iter_ > 0 && dict_size_ > 0) {
    vocab_ = kMeans(descriptors_, dict_size_, max_iter_);
  } else {
    std::cout << "Error updating vocabulary, check dictionary params."
              << std::endl;
  }
}

// Setter methods
void BowDictionary::set_max_iterations(const int max_iter) {
  max_iter_ = max_iter;
  update_vocabulary();
}

void BowDictionary::set_size(const int size) {
  dict_size_ = size;
  update_vocabulary();
}

void BowDictionary::set_descriptors(const std::vector<cv::Mat> &descriptors) {
  descriptors_ = descriptors;
  update_vocabulary();
}

int BowDictionary::total_features() const {
  int num_features = 0;
  for (const cv::Mat &mat : descriptors_) {
    num_features += mat.rows;
  }
  return num_features;
}