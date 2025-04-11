#ifndef IO_STRATEGY_HPP
#define IO_STRATEGY_HPP

#include "pixel.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace igg {

struct ImageData {
  int rows;
  int cols;
  uint8_t max_val;
  std::vector<Pixel> data;
};

class IoStrategy {
public:
  virtual ImageData ReadFromDisk(const std::string &filename) = 0;
  virtual void WriteToDisk(const ImageData &img_data,
                           const std::string &filename) = 0;
};

class PngIoStrategy : public IoStrategy {
public:
  ImageData ReadFromDisk(const std::string &filename) override;
  void WriteToDisk(const ImageData &img_data,
                   const std::string &filename) override;
};

class PpmIoStrategy : public IoStrategy {
public:
  ImageData ReadFromDisk(const std::string &filename) override;
  void WriteToDisk(const ImageData &img_data,
                   const std::string &filename) override;
};
} // namespace igg

#endif