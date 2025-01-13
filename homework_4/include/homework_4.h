#ifndef HOMEWORK_4_H
#define HOMEWORK_4_H

#include <string>
#include <vector>

namespace ipb {

template <typename T>

class named_vector {
private:
  std::string type_name;
  std::vector<T> std_vector;

public:
  named_vector() : type_name(""), std_vector({}){};

  named_vector(const std::string &name, const std::vector<T> &vec)
      : type_name(name), std_vector(vec){};

  std::string name() const { return type_name; };

  std::vector<T> vector() const { return std_vector; };

  void set_name(const std::string &name) { type_name = name;};

  void set_vector(const std::vector<T> &vector) { std_vector = vector;};

  bool empty() { return type_name.empty() || std_vector.empty(); };

  size_t size() { return type_name.size() + std_vector.size(); };

  void resize(size_t n) { std_vector.resize(n); };

  size_t capacity() { return std_vector.capacity(); };

  void reserve(size_t n) { std_vector.reserve(n); };
};
} // namespace ipb

#endif