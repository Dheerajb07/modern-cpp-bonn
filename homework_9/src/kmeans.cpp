#include "kmeans.hpp"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <set>
#include <string>
#include <vector>

cv::Mat get_random_centroids(const cv::Mat &points, const int k,
                             std::vector<int> &labels) {
  // Init Mat to store centroids
  cv::Mat centroids(k, points.cols, points.type());

  // random number generator
  cv::RNG rng(cv::getTickCount());

  // Set to keep track of the selected centroid indices (to ensure uniqueness)
  std::set<int> rand_idx;

  // select random points as centroids
  //   std::cout << "Random centroid indexes: ";
  for (int cluster_idx = 0; cluster_idx < k; cluster_idx++) {
    int point_idx;
    do {
      // Generate random index
      point_idx = rng.uniform(0, points.rows);
    } while (rand_idx.find(point_idx) != rand_idx.end()); // Ensure it's unique

    // Add the unique index to the set
    rand_idx.insert(point_idx);
    // std::cout << point_idx << " ";

    // add row to centroids
    points.row(point_idx).copyTo(centroids.row(cluster_idx));

    // assign cluster number (label) to the centroid
    labels[point_idx] = cluster_idx;
  }
  //   std::cout << std::endl;
  // print_vector(labels, "Label vector");

  return std::move(centroids);
}

std::vector<float> get_distance(const cv::Mat &fromPoint,
                                const cv::Mat &toPoints) {
  int num_points = toPoints.rows;
  // calc dist to points
  std::vector<float> dist(num_points, 0);
  for (int i = 0; i < num_points; i++) {
    dist[i] = cv::norm(fromPoint - toPoints.row(i), cv::NORM_L2);
  }
  return dist;
}

int get_min_idx(const std::vector<float> &vec) {
  auto min_iter = std::min_element(vec.begin(), vec.end());
  int min_idx = std::distance(vec.begin(), min_iter);
  return min_idx;
}

void clusterPoints(const cv::Mat &points, const cv::Mat &centroids,
                   std::vector<cv::Mat> &cluster, std::vector<int> &labels) {
  // number of clusters
  int k = centroids.rows;
  // Initialize each cluster with an empty cv::Mat
  cluster.clear();
  cluster.resize(k, cv::Mat());

  for (int i = 0; i < points.rows; i++) {
    // Take each point
    cv::Mat point = points.row(i);

    if (labels[i] == -1) {
      // assign point to cluster
      // calc dist to k centroids
      std::vector<float> dist = get_distance(point, centroids);

      // get nearest dist idx
      int min_idx = get_min_idx(dist);

      // push point to the cluster
      cluster[min_idx].push_back(point);

      // save point label
      labels[i] = min_idx;
    } else {
      cluster[labels[i]].push_back(point);
    }
  }

  // if a cluster is empty after above assignment
  // push random points into the cluster (use random_centroids)
  //   for (int i = 0; i < k; i++) {
  //     if (cluster[i].rows == 0 && cluster[i].cols == 0) {
  //       cv::Mat rand_points = get_random_centroids(points, k, labels);
  //       cluster[i].push_back(rand_points);
  //     }
  //   }
}

cv::Mat calculate_centroids(const std::vector<cv::Mat> &cluster) {
  // number of clusters
  int k = cluster.size();

  // init centroid matrix
  cv::Mat centroids(k, cluster[0].cols, cluster[0].type());

  for (int cluster_idx = 0; cluster_idx < k; cluster_idx++) {
    // get points in cluster
    cv::Mat points = cluster[cluster_idx];

    // calculate average
    cv::Mat points_avg;
    cv::reduce(points, points_avg, 0, cv::REDUCE_SUM, points.type());
    points_avg = points_avg / points.rows;

    // store centroid
    points_avg.copyTo(centroids.row(cluster_idx));
  }

  return centroids;
}

bool centroid_converge(const cv::Mat &new_centroids,
                       const cv::Mat &old_centroids) {
  // Convergence: L2 norm < 1e-6
  double centroid_diff = cv::norm(old_centroids - new_centroids, cv::NORM_L2);
  if (centroid_diff < 0.1) {
    return true;
  } else {
    return false;
  }
}

float totalWCSS(const std::vector<cv::Mat> &cluster, const cv::Mat &centroids) {
  // Within Cluster Sum-of-Squares : WCSS
  float total_wcss = 0;

  // num clusters
  int k = centroids.rows;
  for (int cluster_idx = 0; cluster_idx < k; cluster_idx++) {
    // get distances of each point to centroid
    std::vector<float> dist =
        get_distance(centroids.row(cluster_idx), cluster[cluster_idx]);
    float wcss =
        std::inner_product(dist.begin(), dist.end(), dist.begin(), 0.0f);

    total_wcss += wcss;
  }

  return total_wcss;
}

cv::Mat ipb::kMeans(const std::vector<cv::Mat> &dataset, int k, int max_iter) {
  // Stack all descriptors into one cv::Mat
  cv::Mat points;
  cv::vconcat(dataset, points);
  //   std::cout << "Dataset : " << std::endl << points << std::endl;

  // vector of centroids
  std::vector<cv::Mat> centroids_list(max_iter, cv::Mat());

  // vector to store WCSS values : WCSS is an evaluation metric to find the
  // optimal centroids
  std::vector<float> wcss_list(max_iter, 0);

  for (int iter = 0; iter < max_iter; iter++) {
    // cluster vector
    std::vector<cv::Mat> cluster;
    // labels vector
    std::vector<int> labels(points.rows, -1);

    /* 1. Select k centroids randomly from points matrix */
    cv::Mat centroids = get_random_centroids(points, k, labels);

    /* 2. Cluster Points */
    while (true) {
      std::vector<int> temp_labels = labels;
      // cluster points for given centroids
      clusterPoints(points, centroids, cluster, temp_labels);

      // re-calculate cluster centroids after assignment
      cv::Mat new_centroids = calculate_centroids(cluster);

      // check convergence
      if (centroid_converge(new_centroids, centroids)) {
        break;
      }

      // update centroids;
      centroids = new_centroids.clone();
    }

    // Calc WCSS and store
    wcss_list[iter] = totalWCSS(cluster, centroids);

    // store centroids
    centroids_list[iter] = centroids;

    // print iteration data to terminal
    // std::cout << std::endl << "Iteration " << iter << std::endl;
    // print_cluster_data(cluster);
    // std::cout << "Centroids : " << std::endl << centroids << std::endl;
    // std::cout << "Total WCSS : " << std::endl << wcss_list[iter] <<
    // std::endl;
  }

  // get iter idx for min total wcss
  int wcss_min_idx = get_min_idx(wcss_list);

  return centroids_list[wcss_min_idx];
}
