#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <opencv2/core.hpp>
#include <vector>

#include "bow_dictionary.hpp"

namespace ipb {

class Histogram {
private:
    std::vector<int> data_;

public:
    // Constructors
    Histogram(){};
    explicit Histogram(const std::vector<int> &data) : data_(data){};
    Histogram(const cv::Mat &descriptors, const BowDictionary &dictionary);

    // compute histogram
    void compute(const cv::Mat &descriptors, const BowDictionary &dictionary);

    // operator<<();
    void WriteToCSV(const std::string &filename);
    Histogram ReadFromCSV(const std::string &filename);

    // Imitate stl_vector functionality
    int &operator[](int idx) { return data_[idx]; }
    std::vector<int> &data() { return data_; }
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    std::vector<int>::iterator begin() { return data_.begin(); }
    std::vector<int>::iterator end() { return data_.end(); }
    std::vector<int>::const_iterator cbegin() const { return data_.cbegin(); }
    std::vector<int>::const_iterator cend() const { return data_.cend(); }
};
}  // namespace ipb

#endif