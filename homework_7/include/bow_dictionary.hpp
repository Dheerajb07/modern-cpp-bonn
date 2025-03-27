#ifndef BOW_DICTIONARY_HPP
#define BOW_DICTIONARY_HPP

#include <opencv2/core.hpp>

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

  // update vocabulary
  void update_vocabulary();

  // Getter methods
  int max_iterations() const { return max_iter_; }
  int size() const { return dict_size_; }
  const std::vector<cv::Mat> &descriptors() const { return descriptors_; }
  const cv::Mat &vocabulary() const { return vocab_; }

  // Setter methods
  void set_max_iterations(const int max_iter);
  void set_size(const int size);
  void set_descriptors(const std::vector<cv::Mat> &descriptors);

  // other methods
  bool empty() { return vocab_.empty(); }
  int total_features() const;
};

} // namespace ipb
#endif