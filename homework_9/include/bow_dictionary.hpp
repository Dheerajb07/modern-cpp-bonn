#ifndef BOW_DICTIONARY_HPP
#define BOW_DICTIONARY_HPP

#include <opencv2/core.hpp>

namespace ipb {

class BowDictionary {
private:
    cv::Mat vocabulary_ = cv::Mat();  // words

private:
    BowDictionary() = default;
    ~BowDictionary() = default;

public:
    BowDictionary(const BowDictionary &) = delete;
    void operator=(const BowDictionary &) = delete;

    // Init Dictionary Instance
    static BowDictionary &GetInstance();

    // Set dictionary params
    void build(const int max_iter,
               const int size,
               const std::vector<cv::Mat> &descriptors);

    // Getter methods
    const cv::Mat &vocabulary() const { return vocabulary_; }

    // Setter methods
    void set_vocabulary(const cv::Mat &vocab) { vocabulary_ = vocab; }

    // other methods
    bool empty() const { return vocabulary_.empty(); }
    int size() const { return vocabulary_.rows; };
};

}  // namespace ipb
#endif