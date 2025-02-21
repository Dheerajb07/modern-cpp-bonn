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

void Image::WriteToPgm(const std::string &file_name) {
  igg::io_tools::ImageData img_data = {rows_, cols_, max_val_, data_};
  bool write_success = igg::io_tools::WriteToPgm(img_data, file_name);
  if(write_success){
    std::cout << "Image written to pgm file" << std::endl;
  }
  else{
    std::cout << "Error writing image to pgm file" << std::endl;
  }
}
} // namespace igg