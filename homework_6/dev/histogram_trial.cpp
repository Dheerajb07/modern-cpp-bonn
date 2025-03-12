#include "homework_6.h"
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void print_vector(const auto &vec) {
  for (const auto &element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

int main() {
  // pgm file path
  std::string pgm_path = "tests/data/dummy_file.pgm";
  // fill image from pgm
  igg::Image img;
  bool img_load_sucess = img.FillFromPgm(pgm_path);
  if (!img_load_sucess) {
    std::cerr << "Error loading image from pgm file" << std::endl;
    return 1;
  }

  // compute histogram
  std::vector<float> hist = img.ComputeHistogram(9);
  print_vector(hist);

  // sum of histogram shoud be 1
  std::cout << std::accumulate(hist.begin(), hist.end(), 0.0f) << std::endl;

  return 0;
}