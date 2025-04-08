#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "io_strategy.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

namespace igg {
class Image {
public:
  class Pixel {
  public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    Pixel(){};
    Pixel(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b){};
  };

private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<Pixel> data_ = {};
  std::shared_ptr<IoStrategy> io_strategy_ptr_ = nullptr;

public:
  // constructors
  Image(){};
  Image(int row, int col) : rows_(row), cols_(col) {
    data_.resize(row * col, Pixel(0, 0, 0));
  };

  // set IO strategy
  void SetIoStrategy(std::shared_ptr<IoStrategy> strategy_ptr) {
    io_strategy_ptr_ = strategy_ptr;
  };

  // getter functions
  int rows() const { return rows_; };
  int cols() const { return cols_; };
  uint8_t max_value() const { return max_val_; };
  const std::vector<Pixel> &data() const { return data_; };

  // get pixel
  Pixel at(int row, int col) const { return data_[col + row * cols_]; };

  // set pixel
  Pixel &at(int row, int col) { return data_[col + row * cols_]; };

  // downscale image
  void DownScale(int scale);

  // upscale image
  void UpScale(int scale);

  // read image from file
  void ReadFromDisk(const std::string &filename);

  // write image to file
  void WriteToDisk(const std::string &filename);
};

} // namespace igg

#endif