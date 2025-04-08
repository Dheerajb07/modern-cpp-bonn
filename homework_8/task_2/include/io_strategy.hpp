#ifndef IO_STRATEGY_HPP
#define IO_STRATEGY_HPP

#include <string>

namespace igg {
class IoStrategy {
public:
  virtual void ReadFromDisk(const std::string &filename) = 0;
  virtual void WriteToDisk(const std::string &filename) = 0;
};

class PngIoStrategy : public IoStrategy {
public:
  void ReadFromDisk(const std::string &filename) override;
  void WriteToDisk(const std::string &filename) override;
};

class PpmIoStrategy : public IoStrategy {
public:
  void ReadFromDisk(const std::string &filename) override;
  void WriteToDisk(const std::string &filename) override;
};
} // namespace igg

#endif