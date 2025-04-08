#include "image.hpp"

namespace igg {

void Image::ReadFromDisk(const std::string &filename) {
  if (io_strategy_ptr_) {
    io_strategy_ptr_->ReadFromDisk(filename);
  } else {
    std::cerr << "Io Strategy Not Set" << std::endl;
    exit(1);
  }
}

void Image::WriteToDisk(const std::string &filename) {
  if (io_strategy_ptr_) {
    io_strategy_ptr_->WriteToDisk(filename);
  } else {
    std::cerr << "Io Strategy Not Set" << std::endl;
    exit(1);
  }
}

void Image::DownScale(int scale) {
  // new dimensions
  int new_rows_ = rows_ / scale;
  int new_cols = cols_ / scale;
  int new_size_ = new_rows_ * new_cols;

  // new vector to store scaled image data
  std::vector<Image::Pixel> scaled_data = {};

  // loop over data_ : skip/select pixels 'scale' length apart
  for (int i = 0; i < rows_; i += scale) {
    for (int j = 0; j < cols_; j += scale) {
      scaled_data.push_back(data_[i * cols_ + j]);
    }
  }

  // set data
  data_.resize(new_size_, Image::Pixel(0, 0, 0));
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
  std::vector<Image::Pixel> scaled_data_(new_size_);

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
  data_.resize(new_size_, Image::Pixel(0, 0, 0));
  data_ = scaled_data_;
  rows_ = new_rows_;
  cols_ = new_cols_;
}

} // namespace igg