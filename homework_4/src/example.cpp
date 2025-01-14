#include "homework_4.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
  // test named_vector class
  std::string name = "Dheeraj";
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};

  ipb::named_vector<int> n_v(name, v);

  // test ipb_algorithm library
  ipb::print(n_v);

  std::cout << "[accumulate] " << ipb::accumulate(n_v) << std::endl;

  std::cout << "[count] " << ipb::count(n_v, 5) << std::endl;

  std::cout << "[all_even] " << ipb::all_even(n_v) << std::endl;

  std::cout << "[find] " << ipb::find(n_v, 99) << std::endl;

  ipb::clamp(n_v, 0, 5);
  std::cout << "[clamp] ";
  ipb::print(n_v);

  ipb::fill(n_v, 99);
  std::cout << "[fill] ";
  ipb::print(n_v);

  ipb::toupper(n_v);
  std::cout << "[toupper] ";
  ipb::print(n_v);

  return 0;
}