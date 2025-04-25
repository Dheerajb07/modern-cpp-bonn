#ifndef HISTOGRAM_UTILS_HPP
#define HISTOGRAM_UTILS_HPP

#include <opencv2/core.hpp>
#include <vector>

namespace ipb {
/**
 * @brief  L2 distance from one descriptor to every row in a set.
 * @param[in]  fromPoint  1×D `cv::Mat` (CV_32F) descriptor.
 * @param[in]  toPoints   N×D `cv::Mat` (CV_32F) descriptors/vocabulary.
 * @return  `std::vector<float>` of N distances.
 */
std::vector<float> L2distance(const cv::Mat &fromPoint,
                              const cv::Mat &toPoints);

/**
 * @brief  Return the index of the first minimum value in a vector.
 * @param[in]  vec  'std::vector' to scan.
 * @return  Zero-based index, or -1 if empty.
 */
int argminDist(const std::vector<float> &vec);

}  // namespace ipb

#endif