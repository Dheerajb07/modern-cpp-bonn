#include "bow_dictionary.hpp"

#include "kmeans.hpp"

namespace ipb {

// get singleton object instance
BowDictionary &BowDictionary::GetInstance() {
    static BowDictionary instance;
    return instance;
}

// Set bow_dict params
void BowDictionary::build(const int max_iter,
                          const int size,
                          const std::vector<cv::Mat> &descriptors) {
    // create vocabulary using the above params
    this->vocabulary_ = kMeans(descriptors, size, max_iter);
}

}  // namespace ipb