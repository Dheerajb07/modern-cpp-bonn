#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <cstdint>
#include <string>
#include <vector>

namespace igg {
class Image {
private:
  int rows_;
  int cols_;
  uint8_t max_val_ = 255;
  std::vector<uint8_t> data_{};

public:
  Image(){};
  Image(int rows, int cols) : rows_(rows), cols_(cols) {};

  int rows() const { return rows_; };
  int cols() const { return cols_; };
  uint8_t max_value() const {return max_val_;};
  const std::vector<uint8_t>& data() const {return data_;};

  uint8_t &at(int row, int col) { return data_[row * cols_ + col]; };

  bool FillFromPgm(const std::string &file_name); 

  void WriteToPgm(const std::string &file_name);
};
} // namespace igg

#endif