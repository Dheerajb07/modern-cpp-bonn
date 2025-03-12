#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <cstdint>
#include <string>
#include <vector>

namespace igg {
class Image {
private:
  int rows_ = 0;
  int cols_ = 0;
  uint8_t max_val_ = 255;
  std::vector<uint8_t> data_{};

public:
  Image(){};
  Image(int rows, int cols) : rows_(rows), cols_(cols) {
    data_.resize(rows * cols, 0);
  };

  // getter functions
  int rows() const { return rows_; };
  int cols() const { return cols_; };
  uint8_t max_value() const { return max_val_; };
  const std::vector<uint8_t> &data() const { return data_; };

  // retrieve pixel value at index (row,col)
  uint8_t at(int row, int col) const { return data_[row * cols_ + col]; };

  // fill pixel value at index (row,col)
  uint8_t &at(int row, int col) { return data_[row * cols_ + col]; };

  // fill image data from pgm file
  bool FillFromPgm(const std::string &file_name);

  // write image data to pgm file
  void WriteToPgm(const std::string &file_name);

  std::vector<float> ComputeHistogram(int bins) const;
};
} // namespace igg

#endif