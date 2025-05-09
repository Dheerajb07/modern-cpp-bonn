#include "histogram_utils.hpp"

namespace ipb {

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

std::vector<int> split_string(std::string &s, const std::string &delimiter) {
    std::vector<int> data;
    size_t pos = 0;
    int token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = stoi(s.substr(0, pos));
        data.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    data.push_back(stoi(s));

    return data;
}

}  // namespace ipb