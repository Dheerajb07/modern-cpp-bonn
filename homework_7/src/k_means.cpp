#include "k_means.hpp"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <set>
#include <string>
#include <vector>

/***********************
 * FUNCTION PROTOTYPES
 ***********************/
// k_means funcs
void get_random_centroids(const cv::Mat &points, const int k,
                          cv::Mat &centroids);

int get_min_idx(const std::vector<float> &vec);

std::vector<float> calculate_distances(cv::Mat fromPoint, cv::Mat toPoints);

void clusterPoints(const cv::Mat &points, const cv::Mat &centroids,
                   std::vector<cv::Mat> &cluster);

void calculate_centroids(const std::vector<cv::Mat> &cluster,
                         cv::Mat &centroids);

std::vector<float> calculate_varaince(const std::vector<cv::Mat> &cluster,
                                      const cv::Mat &centroids);

// print funcs
void print_vector(const std::vector<float> &vec, const std::string &vec_name);
void print_mat_data(const cv::Mat &mat, const std::string &mat_name);
void print_cluster_data(const std::vector<cv::Mat> &cluster);

/********************************
 * K-MEANS CLUSTERING ALGORITHM
 ********************************/
cv::Mat ipb::kMeans(const std::vector<cv::Mat> &dataset, int k, int max_iter) {
  // Stack all descriptors into one cv::Mat
  cv::Mat points;
  cv::vconcat(dataset, points);
  print_mat_data(points, "points");

  // 0. create an unordered map to store centroids and variations for each
  // iteration
  // std::vector<cv::Mat> centroid_list;
  // std::vector<float> total_variance;

  /* 1. Select k centroids randomly from points mat */
  cv::Mat centroids;
  get_random_centroids(points, k, centroids);
  std::cout << "Randomized centroids" << std::endl << centroids << std::endl;
  // print_mat_data(centroids, "centroids"); // sanity check

  std::vector<cv::Mat> cluster;
  /* 2. Cluster Points */
  for (int iter = 0; iter < max_iter; iter++) {
    std::cout << std::endl;
    std::cout << "Iteration  " << iter << "..." << std::endl;

    // while (true) {
    // cluster points based on the centroids
    clusterPoints(points, centroids, cluster);

    print_cluster_data(cluster); // sanity check clusters

    // Re-calulate centroids
    cv::Mat new_centroids = centroids.clone();
    calculate_centroids(cluster, new_centroids);

    // Convergence: L2 norm < 1e-6
    auto centroid_diff = cv::norm(centroids - new_centroids, cv::NORM_L2);
    // std::cout << "centroid Norm: " << centroid_diff << std::endl;
    if (centroid_diff < 1e-6) {
      // std::cout << "Clusters converged in " << iter << " iterations!"
      //           << std::endl;
      std::cout << "Converged Centroids" << std::endl;
      std::cout << centroids << std::endl;
      break;
    }

    // update centroids;
    centroids = new_centroids.clone();
    // }
    /* 3. calculate total variance for the current kmeans iteration */
    // calc variance of each cluster
    // std::vector<float> variance = calculate_varaince(cluster, centroids);

    // calc sum of variance
    // float variance_sum =
    //     std::accumulate(variance.begin(), variance.end(), 0.0f);
    // total_variance.push_back(variance_sum);
    // std::cout << "Total Variance : " << variance_sum << std::endl;

    // save centroids to list
    // centroid_list.push_back(centroids.clone());

    // print_mat_data(centroids, "centroids");
  }

  // print_vector(total_variance, "TotalVariance Vector");

  /* TODO: return centroid with minimum variance */
  // get lowest total variance idx
  // int min_var_idx = get_min_idx(total_variance);
  // std::cout << min_var_idx << std::endl;

  return centroids;
}

/*********************
 * K_MEANS FUNCTIONS
 *********************/
void get_random_centroids(const cv::Mat &points, const int k,
                          cv::Mat &centroids) {
  // random number generator
  cv::RNG rng(cv::getTickCount());

  // Set to keep track of the selected centroid indices (to ensure uniqueness)
  std::set<int> rand_idx;

  // select random points as centroids
  std::cout << "centroids indexes: ";
  for (int i = 0; i < k; i++) {
    int idx;
    do {
      // Generate random index
      idx = rng.uniform(0, points.rows);
    } while (rand_idx.find(idx) != rand_idx.end()); // Ensure it's unique

    // Add the unique index to the set
    rand_idx.insert(idx);
    std::cout << idx << " ";

    // add row to centroids
    centroids.push_back(points.row(idx));
  }
  std::cout << std::endl;
}

// void get_random_centroids(const cv::Mat &points, const int k, cv::Mat
// &centroids) {
//   int num_points = points.rows;
//   if (num_points == 0 || k <= 0) return;

//   // if (k > num_points) k = num_points;  // Ensure k is valid

//   // Reset centroids matrix
//   centroids = cv::Mat();

//   // Random number generator
//   cv::RNG rng;

//   // Set to track selected centroid indices
//   std::set<int> selected_indices;

//   // Step 1: Select the first centroid randomly
//   int first_centroid_idx = rng.uniform(0, num_points);
//   centroids.push_back(points.row(first_centroid_idx));
//   selected_indices.insert(first_centroid_idx);

//   // Step 2: Select the remaining centroids using K-means++ initialization
//   for (int i = 1; i < k; ++i) {
//     std::vector<double> distances(num_points);
//     double total_distance = 0;

//     // Step 2.1: Compute squared distances
//     for (int j = 0; j < num_points; ++j) {
//       double min_distance = std::numeric_limits<double>::max();
//       for (int m = 0; m < i; ++m) {
//         double distance = cv::norm(points.row(j) - centroids.row(m),
//         cv::NORM_L2); double squared_distance = distance * distance;
//         min_distance = std::min(min_distance, squared_distance);
//       }
//       distances[j] = min_distance;
//       total_distance += min_distance;
//     }

//     // Step 2.2: Choose the next centroid, ensuring uniqueness
//     int selected_centroid_idx = -1;
//     while (true) {
//       double random_value = rng.uniform(0.0, total_distance);
//       double cumulative_distance = 0;

//       for (int j = 0; j < num_points; ++j) {
//         cumulative_distance += distances[j];
//         if (cumulative_distance >= random_value) {
//           if (selected_indices.find(j) == selected_indices.end()) {  //
//           Ensure uniqueness
//             selected_centroid_idx = j;
//             break;
//           }
//         }
//       }

//       if (selected_centroid_idx != -1) break;  // Stop when we find a unique
//       centroid
//     }

//     // Add the selected centroid
//     centroids.push_back(points.row(selected_centroid_idx));
//     selected_indices.insert(selected_centroid_idx);
//   }
// }

int get_min_idx(const std::vector<float> &vec) {
  auto min_iter = std::min_element(vec.begin(), vec.end());
  int min_idx = std::distance(vec.begin(), min_iter);
  return min_idx;
}

void clusterPoints(const cv::Mat &points, const cv::Mat &centroids,
                   std::vector<cv::Mat> &cluster) {
  // std::cout << points << std::endl;
  // number of clusters
  int k = centroids.rows;
  // Initialize each cluster with an empty cv::Mat
  cluster.resize(k, cv::Mat());

  for (int i = 0; i < points.rows; i++) {
    // Take each point
    cv::Mat point = points.row(i);

    // calc dist to k centroids
    std::vector<float> dist(k, 0);
    for (int j = 0; j < k; j++) {
      dist[j] = cv::norm(point - centroids.row(j), cv::NORM_L2);
    }
    // print_vector(dist, "dist");
    // get nearest dist idx
    int min_idx = get_min_idx(dist);
    // std::cout << min_idx << std::endl;

    // push point to the cluster
    cluster[min_idx].push_back(point);
  }

  // if a cluster is empty after above assignment
  // push random points into the cluster (use random_centroids)
  for (int i = 0; i < k; i++) {
    if (cluster[i].rows == 0 && cluster[i].cols == 0) {
      cv::Mat rand_points;
      get_random_centroids(points, k, rand_points);
      cluster[i].push_back(rand_points);
    }
  }
}

void calculate_centroids(const std::vector<cv::Mat> &cluster,
                         cv::Mat &centroids) {
  // number of clusters
  int k = cluster.size();
  for (int cluster_idx = 0; cluster_idx < k; cluster_idx++) {
    // int cluster_idx = entry.first;
    // std::cout << "Cluster Index : " << cluster_idx << std::endl;

    // get points in cluster
    cv::Mat points = cluster[cluster_idx];
    std::cout << points << std::endl;
    //  calc centroid only if cluster not-empty
    if (!points.empty()) {
      // calculate average
      cv::Mat points_avg;
      cv::reduce(points, points_avg, 0, cv::REDUCE_SUM, points.type());
      points_avg = points_avg / points.rows;

      // store centroid
      std::cout << points_avg << std::endl;
      points_avg.copyTo(centroids.row(cluster_idx));
    }
  }
  // std::cout << "Recalculated centroids" << std::endl << centroids <<
  // std::endl;
}

std::vector<float> calculate_varaince(const std::vector<cv::Mat> &cluster,
                                      const cv::Mat &centroids) {
  std::cout << "Variance Calculation ..." << std::endl;
  // no of clusters
  int k = centroids.rows;
  // init vector
  std::vector<float> variance(k, 1e6);

  for (int cluster_idx = 0; cluster_idx < k; cluster_idx++) {
    // get mean for cluster
    cv::Mat mean = centroids.row(cluster_idx);
    cv::Mat points = cluster[cluster_idx];
    if (points.empty()) {
      continue;
    }
    // Distance Vector
    // calc dist of each point to centroid
    std::vector<float> dist(points.rows, 1e6);
    for (int point_idx = 0; point_idx < points.rows; point_idx++) {
      dist[point_idx] = cv::norm(points.row(point_idx) - mean, cv::NORM_L2);
    }
    print_vector(dist, "distance");

    // Compute mean
    float avg = std::accumulate(dist.begin(), dist.end(), 0.0) / dist.size();
    std::cout << "Mean: " << avg << std::endl;
    // Compute variance
    float sigma_2 =
        std::accumulate(dist.begin(), dist.end(), 0.0,
                        [avg](float sum, float value) {
                          return sum + (value - avg) * (value - avg);
                        }) /
        dist.size();
    std::cout << "Variance: " << sigma_2 << std::endl;
    variance[cluster_idx] = sigma_2;
  }
  print_vector(variance, "variance vector");
  return variance;
}

/**
 * PRINT FUNCTIONS (DEBUGGING)
 */
void print_vector(const std::vector<float> &vec, const std::string &vec_name) {
  std::cout << vec_name << ": ";
  for (auto &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

void print_mat_data(const cv::Mat &mat, const std::string &mat_name) {
  std::cout << mat_name << " size: " << mat.rows << 'x' << mat.cols
            << std::endl;
}

void print_cluster_data(const std::vector<cv::Mat> &cluster) {
  int k = cluster.size();
  int total_points = 0;
  for (int i = 0; i < k; i++) {
    std::string cluster_name = "cluster";
    cluster_name = cluster_name + std::to_string(i + 1);

    print_mat_data(cluster[i], cluster_name);

    total_points += cluster[i].rows;
  }
  std::cout << "Total points in clusters: " << total_points << std::endl;
}
