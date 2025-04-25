#include "histogram_utils.hpp"

std::vector<float> L2distance(const cv::Mat &fromPoint,
                              const cv::Mat &toPoints) {
    int num_points = toPoints.rows;
    // calc dist to points
    std::vector<float> dist(num_points, 0);
    for (int i = 0; i < num_points; i++) {
        dist[i] = cv::norm(fromPoint - toPoints.row(i), cv::NORM_L2);
    }
    return dist;
}

int argminDist(const std::vector<float> &vec) {
    auto min_iter = std::min_element(vec.begin(), vec.end());
    int min_idx = std::distance(vec.begin(), min_iter);
    return min_idx;
}