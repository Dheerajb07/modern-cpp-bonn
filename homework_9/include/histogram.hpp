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

    // stream and access operators
    friend std::ostream &operator<<(std::ostream &os, const Histogram &hist);
    int operator[](std::size_t idx) const { return data_.at(idx); }
    int &operator[](std::size_t idx) { return data_.at(idx); }

    // Imitate stl_vector functionality
    std::vector<int> &data() { return data_; }
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    std::vector<int>::iterator begin() { return data_.begin(); }
    std::vector<int>::iterator end() { return data_.end(); }
    std::vector<int>::const_iterator cbegin() const { return data_.cbegin(); }
    std::vector<int>::const_iterator cend() const { return data_.cend(); }

    // Read - Write static members
    static void WriteToCSV(const std::string &filename, const Histogram &hist);
    static Histogram ReadFromCSV(const std::string &filename);
};
}  // namespace ipb

#endif