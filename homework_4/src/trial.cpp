#include "homework_4.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string name = "Dheeraj";
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};

  ipb::named_vector<int> n_v(name, v);

  std::cout << n_v.name() << std::endl;

  std::cout << n_v.vector()[0] << std::endl;

  return 0;
}