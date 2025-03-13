#include "image.hpp"
#include "io_tools/io_tools.hpp"
#include <iostream>

namespace igg {

bool Image::FillFromPgm(const std::string &file_name) {
  igg::io_tools::ImageData img_data = igg::io_tools::ReadFromPgm(file_name);
  if (!img_data.data.empty()) {
    rows_ = img_data.rows;
    cols_ = img_data.cols;
    max_val_ = img_data.max_val;
    data_ = img_data.data;
    return true;
  }
  return false;
}

void Image::WriteToPgm(const std::string &file_name) const {
  igg::io_tools::ImageData img_data = {rows_, cols_, max_val_, data_};
  bool write_success = igg::io_tools::WriteToPgm(img_data, file_name);
  if (write_success) {
    std::cout << "Image written to pgm file" << std::endl;
  } else {
    std::cout << "Error writing image to pgm file" << std::endl;
  }
}

std::vector<float> Image::ComputeHistogram(int bins) const {
  std::vector<float> histogram(bins, 0);
  float bin_range = float(max_val_) / bins;
  for (const auto &pixel : data_) {
    int idx = bins - 1;
    if (pixel < max_val_) {
      idx = pixel / bin_range;
    }
    histogram[idx] += 1.0f / (rows_ * cols_);
  }
  return histogram;
}

void Image::DownScale(int scale) {
  // new dimensions
  int new_rows_ = rows_ / scale;
  int new_cols = cols_ / scale;
  int new_size_ = new_rows_ * new_cols;

  // new vector to store scaled image data
  std::vector<uint8_t> scaled_data = {};

  // loop over data_ : skip/select pixels 'scale' length apart
  for (int i = 0; i < rows_; i += scale) {
    for (int j = 0; j < cols_; j += scale) {
      scaled_data.push_back(data_[i * cols_ + j]);
    }
  }

  // set data
  data_.resize(new_size_, 0);
  data_ = scaled_data;
  rows_ = new_rows_;
  cols_ = new_cols;
}

void Image::UpScale(int scale) {
  // new dimensions
  int new_rows_ = rows_ * scale;
  int new_cols_ = cols_ * scale;
  int new_size_ = new_rows_ * new_cols_;

  // new vector to store scaled image data
  std::vector<uint8_t> scaled_data_(new_size_, 0);

  // loop over data_ : fill pixels
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      // fill pixel and neighbours
      for (int r = i * scale; r < (i + 1) * scale; r++) {
        for (int c = j * scale; c < (j + 1) * scale; c++) {
          scaled_data_[r * cols_ * scale + c] = data_[i * cols_ + j];
        }
      }
    }
  }

  // set data
  data_.resize(new_size_, 0);
  data_ = scaled_data_;
  rows_ = new_rows_;
  cols_ = new_cols_;
}
} // namespace igg