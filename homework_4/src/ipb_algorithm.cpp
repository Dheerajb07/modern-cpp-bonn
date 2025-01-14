#include "homework_4.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>

namespace ipb {

int accumulate(ipb::named_vector<int> &v) {
  int sum = std::accumulate(v.vector().begin(), v.vector().end(), 0);
  return sum;
}

int count(ipb::named_vector<int> &v, int num) {
  int count = std::count(v.vector().begin(), v.vector().end(), num);
  return count;
}

bool all_even(ipb::named_vector<int> &v) {
  for (const int m : v.vector()) {
    if (m % 2 != 0) {
      return false;
    };
  }
  return true;
}

void clamp(ipb::named_vector<int> &v, int min, int max) {
  std::vector<int> v_temp = v.vector();
  for (int i = 0; i < v_temp.size(); i++) {
    v_temp[i] = std::clamp(v_temp[i], min, max);
  }
  v.set_vector(v_temp);
}

void fill(ipb::named_vector<int> &v, int num) {
  std::fill(v.vector().begin(), v.vector().end(), num);
}

bool find(ipb::named_vector<int> &v, int num) {
  std::vector<int>::iterator idx =
      std::find(v.vector().begin(), v.vector().end(), num);
  if (idx != v.vector().end()) {
    return true;
  } else {
    return false;
  }
}

void print(ipb::named_vector<int> &v) {
  std::cout << v.name() << " : ";
  for (const int elem : v.vector()) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

void toupper(ipb::named_vector<int> &v) {
  // loop over each char in string
  for (char &c : v.name()) {
    // convert each char to uppercase
    c = std::toupper(c);
  }
}

void sort(ipb::named_vector<int> &v) {
  // sort vector using STL
  std::sort(v.vector().begin(), v.vector().end());
}

void rotate(ipb::named_vector<int> &v, int pos) {
  // create iterator
  std::vector<int>::iterator rot_iter = v.vector().begin();
  // advance iterator to the index to be rotated
  std::advance(rot_iter, pos);
  // rotate vector using STL
  rot_iter = std::rotate(v.vector().begin(), rot_iter, v.vector().end());
}

void reverse(ipb::named_vector<int> &v) {
  // reverse vector using STL
  std::reverse(v.vector().begin(), v.vector().end());
}
} // namespace ipb