#include "kmeans.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat ipb::kMeans(const std::vector<cv::Mat> &dataset, int k,
                      int max_iter) {
  // Step 1: Stack all descriptors into one cv::Mat
  cv::Mat points;
  cv::vconcat(dataset, points);
//   std::cout << "Dataset : " << std::endl << points << std::endl;

  // Step 2: Run the OpenCV k-means algorithm
  cv::Mat labels;  // Holds the cluster assignments for each data point
  cv::Mat centers; // Holds the cluster centers (centroids)

  // Perform k-means clustering
  cv::kmeans(
      points, k, labels,
      cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
                       max_iter, 0.1),
      10, cv::KMEANS_PP_CENTERS, centers);

  // Step 3: Return the cluster centroids
  return centers;
}