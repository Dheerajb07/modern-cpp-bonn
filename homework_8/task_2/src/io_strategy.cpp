#include "io_strategy.hpp"
#include "string_utils.hpp"
#include <filesystem>
#include <png++/png.hpp>

namespace igg {

/*
 *  UTILITY FUNCTIONS
 */
Pixel convert2IggPixel(const png::rgb_pixel &png_pixel) {
  Pixel igg_pixel(png_pixel.red, png_pixel.green, png_pixel.blue);
  return igg_pixel;
}

png::rgb_pixel convert2PngPixel(const Pixel &igg_pixel) {
  png::rgb_pixel png_pixel(igg_pixel.red, igg_pixel.green, igg_pixel.blue);
  return png_pixel;
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

    // push to pixel vector
    pixel_vec.push_back(igg::Pixel(r, g, b));

    // increment
    i += 3;
  }

  return pixel_vec;
}

/*
 *  PNG_IO_STRATEGY
 */
ImageData PngIoStrategy::ReadFromDisk(const std::string &filename) {
  // read png image
  png::image<png::rgb_pixel> image(filename,
                                   png::require_color_space<png::rgb_pixel>());

  // init struct to store data
  ImageData img_data;

  // Get the width and height of the image
  int n_rows = image.get_height();
  int n_cols = image.get_width();

  // store data
  img_data.rows = n_rows;
  img_data.cols = n_cols;

  // resize data vector
  img_data.data.resize(n_rows * n_cols, Pixel(0, 0, 0));

  // convert png_pixels to igg_pixels
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      img_data.data[i * n_cols + j] = convert2IggPixel(image[i][j]);
    }
  }

  return img_data;
}

void PngIoStrategy::WriteToDisk(const ImageData &img_data,
                                const std::string &filename) {
  // get no of rows and cols
  int n_rows = img_data.rows;
  int n_cols = img_data.cols;

  // init png_image
  png::image<png::rgb_pixel> image(n_cols, n_rows);

  // fill image
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      image[i][j] = convert2PngPixel(img_data.data[i * n_cols + j]);
    }
  }

  // write image
  image.write(filename);
}

/*
 *  PPM_IO_STRATEGY
 */
ImageData PpmIoStrategy::ReadFromDisk(const std::string &filename) {
  // Open the file using ifstream for reading
  std::ifstream file(filename);

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

  ImageData img_data;
  img_data.rows = n_rows;
  img_data.cols = n_cols;
  img_data.max_val = max_value;
  img_data.data = data;

  return img_data;
}

void PpmIoStrategy::WriteToDisk(const ImageData &img_data,
                                const std::string &filename) {
  // img type var
  std::string img_type = "P3";

  // Open the file using ofstream for writing
  std::ofstream file(filename);

  // Check if the file opened successfully
  if (file.is_open()) {
    // Line 0: Image type
    file << img_type << " " << std::endl;

    // Line 1: width x height
    file << img_data.cols << " " << img_data.rows << " " << std::endl;

    // Line 2: max_value
    file << static_cast<int>(img_data.max_val) << " " << std::endl;

    int char_count = 0;
    // Line 3 and onwards: pixels
    for (const igg::Pixel &pxl : img_data.data) {
      // if charecter count exceeds 70 move to next line
      if (char_count >= 70) {
        file << std::endl;
        char_count = 0;
      }
      // write each pixel
      std::string pxl_str = std::to_string(static_cast<int>(pxl.red)) + " " +
                            std::to_string(static_cast<int>(pxl.green)) + " " +
                            std::to_string(static_cast<int>(pxl.blue)) + " ";
      file << pxl_str;

      char_count += pxl_str.size();
    }

  } else {
    std::cerr << "Failed to open the file." << std::endl;
    exit(1);
  }
}

} // namespace igg