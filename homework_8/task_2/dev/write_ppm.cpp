#include "pixel.hpp"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string filename = "../data/wrte_ascii.ppm";

  // int vars
  std::string img_type = "P3";
  int n_rows = 300;
  int n_cols = 300;
  int max_value = 255;
  std::vector<igg::Pixel> data(n_cols * n_rows, igg::Pixel(0, 0, 0));

  // Open the file using ofstream for writing
  std::ofstream file(filename);

  // Check if the file opened successfully
  if (file.is_open()) {
    // Line 0: Image type = "P3"
    file << img_type << " " << std::endl;

    // Line 1: width x height
    file << n_cols << " " << n_rows << " " << std::endl;

    // Line 2: max_value
    file << max_value << " " << std::endl;

    // Line 3 and onwards: pixels
    for (const igg::Pixel p : data) {
    }
  }

  return 0;
}