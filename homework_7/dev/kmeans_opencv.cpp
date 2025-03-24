#include <opencv2/opencv.hpp>
#include <vector>

std::vector<cv::Mat> &GetDummyData() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  static std::vector<cv::Mat> data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 5; j++) {
      data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

cv::Mat GetAllFeatures() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  for (int i = 0; i < 100; i += 20) {
    for (size_t j = 0; j < 5; j++) {
      data.push_back(cv::Mat_<float>(rows_num, cols_num, i));
    }
  }

  return data;
}

cv::Mat Get3Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  data.push_back(cv::Mat_<float>(rows_num, cols_num, 0.0F));
  data.push_back(cv::Mat_<float>(rows_num, cols_num, 30.0F));
  data.push_back(cv::Mat_<float>(rows_num, cols_num, 70.0F));

  return data;
}

cv::Mat Get2Kmeans() {
  // init some parameters
  const int rows_num = 1;
  const int cols_num = 10;
  cv::Mat data;

  data.push_back(cv::Mat_<float>(rows_num, cols_num, 20.000002F));
  data.push_back(cv::Mat_<float>(rows_num, cols_num, 70.0F));

  return data;
}

cv::Mat kMeans_opencv(const std::vector<cv::Mat> &dataset, int k,
                      int max_iter) {
  // Step 1: Stack all descriptors into one cv::Mat
  cv::Mat points;
  cv::vconcat(dataset, points);
  std::cout << "Dataset : " << std::endl << points << std::endl;

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

int main() {
  // Dataset
  auto dataset = GetDummyData();
  // solution
  // auto gt_cluster = GetAllFeatures();
  auto gt_cluster = Get3Kmeans();

  // K-Means
  const int dict_size = gt_cluster.rows;
  const int iterations = 10;
  cv::Mat centroids = kMeans_opencv(dataset, dict_size, iterations);
  cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);

  std::cout << " Calculated centroids : " << std::endl
            << centroids << std::endl;

  std::cout << "Correct centriods : " << std::endl << gt_cluster << std::endl;

  return 0;
}
