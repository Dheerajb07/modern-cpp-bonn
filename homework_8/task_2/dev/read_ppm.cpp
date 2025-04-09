#include "pixel.hpp"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string trim(const std::string &str,
                 const std::string &whitespace = " \t") {
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content

  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}

std::string reduce(const std::string &str, const std::string &fill = " ",
                   const std::string &whitespace = " \t") {
  // trim first
  auto result = trim(str, whitespace);

  // replace sub ranges
  auto beginSpace = result.find_first_of(whitespace);
  while (beginSpace != std::string::npos) {
    const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
    const auto range = endSpace - beginSpace;

    result.replace(beginSpace, range, fill);

    const auto newStart = beginSpace + fill.length();
    beginSpace = result.find_first_of(whitespace, newStart);
  }

  return result;
}

std::vector<std::string> split(std::string &s,
                               const std::string &delimiter = " ") {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}

std::vector<igg::Pixel> getPixels(const std::vector<std::string> &str_vec) {
  // init vector
  std::vector<igg::Pixel> pixel_vec = {};

  size_t i = 0;
  while (i < str_vec.size() - 2) {
    // get r,g,b values
    uint8_t r = static_cast<uint8_t>(stoi(str_vec[i]));
    uint8_t g = static_cast<uint8_t>(stoi(str_vec[i + 1]));
    uint8_t b = static_cast<uint8_t>(stoi(str_vec[i + 2]));

    std::cout << "{R: " << static_cast<int>(r) << ", "
              << "G: " << static_cast<int>(g) << ", "
              << "B: " << static_cast<int>(b) << "}" << std::endl;

    // push to pixel vector
    pixel_vec.push_back(igg::Pixel(r, g, b));

    // increment
    i += 3;
  }

  return pixel_vec;
}

int main() {
  // Open the file using ifstream for reading
  std::ifstream file("../data/pbmlib.ascii.ppm");

  // image data variables
  std::string type;
  int n_rows = 0;
  int n_cols = 0;
  int max_value = 0;
  std::vector<igg::Pixel> data = {};

  // Check if the file opened successfully
  if (file.is_open()) {
    // init variables
    std::string line;
    int line_num = 0;

    // Read the file line by line
    while (std::getline(file, line)) {
      // trim leading and trailing whitespaces
      line = trim(line);

      // skip commented lines
      if (line.front() == '#') {
        continue;
      }

      // reduce whitespaces
      line = reduce(line);

      // line 0: image type
      if (line_num == 0) {
        type = split(line)[0];
      }

      // line 1: width x height - image size
      else if (line_num == 1) {
        // split line into words
        std::vector<std::string> words = split(line);
        // get rows, cols
        n_rows = stoi(words[1]);
        n_cols = stoi(words[0]);
      }

      // line 2: max_value
      else if (line_num == 2) {
        // split line into words
        std::vector<std::string> words = split(line);
        // get max_value
        max_value = stoi(words[0]);
      }

      // line 3 and onwards: pixel values
      else {
        std::cout << line << std::endl;
        // split line into substrings
        std::vector<std::string> words = split(line);
        // get pixels from substrings
        std::vector<igg::Pixel> pixel_vec = getPixels(words);
        // append pixels to data vector
        data.insert(data.end(), pixel_vec.begin(), pixel_vec.end());
      }

      line_num++;
    }

    file.close(); // Close the file when done

  } else {
    std::cerr << "Failed to open the file." << std::endl;
    exit(1);
  }

  // Print Image Data
  std::cout << "Type: " << type << std::endl;
  std::cout << "Rows: " << n_rows << ", "
            << "Cols: " << n_cols << std::endl;
  std::cout << "Max Val: " << max_value << std::endl;
  std::cout << "Vector size: " << data.size() << std::endl;

  return 0;
}