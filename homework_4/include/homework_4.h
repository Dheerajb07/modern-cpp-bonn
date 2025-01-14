#ifndef HOMEWORK_4_H
#define HOMEWORK_4_H

#include <string>
#include <vector>

namespace ipb {

/*
  CLASS NAMED_VECTOR
*/

template <typename T>

class named_vector {
private:
  std::string type_name;
  std::vector<T> std_vector;

public:
  named_vector() : type_name(""), std_vector({}){};

  named_vector(const std::string &name, const std::vector<T> &vec)
      : type_name(name), std_vector(vec){};

  std::string &name() { return type_name; };

  std::vector<T> &vector() { return std_vector; };

  void set_name(const std::string &name) { type_name = name; };

  void set_vector(const std::vector<T> &vector) { std_vector = vector; };

  bool empty() { return type_name.empty() || std_vector.empty(); };

  size_t size() { return type_name.size() + std_vector.size(); };

  void resize(size_t n) { std_vector.resize(n); };

  size_t capacity() { return std_vector.capacity(); };

  void reserve(size_t n) { std_vector.reserve(n); };
};

/*
  LIBRARY IPB_ALGORITHM
*/

int accumulate(ipb::named_vector<int> &named_vector);

int count(ipb::named_vector<int> &named_vector, int num);

bool all_even(ipb::named_vector<int> &named_vector);

void clamp(ipb::named_vector<int> &named_vector,int min, int max);

void fill(ipb::named_vector<int> &named_vector, int num);

bool find(ipb::named_vector<int> &named_vector, int num);

void print(ipb::named_vector<int> &named_vector);

void toupper(ipb::named_vector<int> &named_vector);

void sort(ipb::named_vector<int> &named_vector);

void rotate(ipb::named_vector<int> &named_vector, int pos);

void reverse(ipb::named_vector<int> &named_vector);

} // namespace ipb

#endif