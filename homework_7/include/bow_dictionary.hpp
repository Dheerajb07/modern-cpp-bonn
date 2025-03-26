#ifndef BOW_DICTIONARY_HPP
#define BOW_DICTIONARY_HPP

#include "kmeans.hpp"
#include <opencv2/core.hpp>
#include <vector>

namespace ipb {

class BowDictionary {
private:
  int max_iter_ = 0;                      // max iterations for kmeans
  int dict_size_ = 0;                     // no. of clusters
  std::vector<cv::Mat> descriptors_ = {}; // dataset
  cv::Mat vocab_ = cv::Mat();             // cluster centroids

private:
  BowDictionary() = default;
  ~BowDictionary() = default;

public:
  BowDictionary(const BowDictionary &) = delete;
  void operator=(const BowDictionary &) = delete;

  // Init Dictionary Instance
  static BowDictionary &GetInstance();

  // Set dictionary params
  void set_params(const int max_iter, const int size,
                  const std::vector<cv::Mat> &descriptors);

  // create vocab from descriptors
  void create_vocabulary() {vocab_ = ipb::kMeans(descriptors_,dict_size_,max_iter_);}
    
  // update vocab when params change
  void update_

  // Getter methods
  int max_iterations() const { return max_iter; }
  int size() const { return dict_size; }
  const std::vector<cv::Mat> &descriptors() const { return descriptors; }
  cv::Mat vocabulary() const { return vocab; }

  // Setter methods
  void set_max_iterations(const int max_iter) { max_iter_ = max_iter; }
  void set_size(const int size) { dict_size_ = size; }
  void set_descriptors(const std::vector<cv::Mat> &descriptors){
      descriptors_ = descriptors};

  // other methods
  bool empty() { return vocab.empty(); }
  int total_features() const;
}

} // namespace ipb
#endif