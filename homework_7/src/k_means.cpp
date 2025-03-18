#include "k_means.hpp"
#include <algorithm>
#include <cstdio>
#include <iostream>
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
void clusterPoints(const cv::Mat &points, const cv::Mat &centroids,
                   std::vector<cv::Mat> &cluster);
void calculate_centroids(const std::vector<cv::Mat> &cluster,
                         cv::Mat &centroids);

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
  std::vector<cv::Mat> centroid_list;
  std::vector<std::vector<float>> variation_list;

  for (int iter = 0; iter < max_iter; iter++) {
    // 1. Select k centroids randomly from points mat
    cv::Mat centroids;
    get_random_centroids(points, k, centroids);
    //   print_mat_data(centroids, "centroids");  // sanity check

    while (true) {
      // cluster points based on the centroids
      std::vector<cv::Mat> cluster;
      clusterPoints(points, centroids, cluster);

      print_cluster_data(cluster); // sanity check clusters

      // Re-calulate centroids
      cv::Mat new_centroids = centroids.clone();
      calculate_centroids(cluster, new_centroids);

      // Convergence: L2 norm < 1e-6
      auto centroid_diff = cv::norm(centroids - new_centroids, cv::NORM_L2);
      std::cout << "centroid Norm: " << centroid_diff << std::endl;
      if (centroid_diff < 1e-6) {
        std::cout << "Clusters converged in " << iter << " iterations!"
                  << std::endl;
        break;
      }

      // update centroids;
      centroids = new_centroids.clone();
    }
    // save centroids to map
    centroid_list.push_back(centroids.clone());

    /* TODO: calc variation */ 

    // print_mat_data(centroids, "centroids");
  }

  /* TODO: return centroid with minimum variance */

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

void clusterPoints(const cv::Mat &points, const cv::Mat &centroids,
                   std::vector<cv::Mat> &cluster) {
  // std::cout << points << std::endl;
  // number of clusters
  int k = centroids.rows;
  // Initialize each cluster with an empty cv::Mat
  for (int i = 0; i < k; i++) {
    cluster.push_back(cv::Mat());
  }

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
    auto min_iter = std::min_element(dist.begin(), dist.end());
    int min_idx = std::distance(dist.begin(), min_iter);
    // std::cout << min_idx << std::endl;

    // push point to the cluster
    cluster[min_idx].push_back(point);
  }
}

void calculate_centroids(const std::vector<cv::Mat> &cluster,
                         cv::Mat &centroids) {
  // number of clusters
  int k = cluster.size();
  for (int cluster_idx = 0; cluster_idx < k; cluster_idx++) {
    // int cluster_idx = entry.first;
    // std::cout << cluster_idx << std::endl;

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
      centroids.row(cluster_idx) = points_avg;
    }
  }
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
