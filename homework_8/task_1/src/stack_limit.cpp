#include <algorithm>
#include <array>
#include <iostream>

void allocate_memory_on_stack(int i) {
  std::array<double, (100 * 1024 / sizeof(double))> arr;
  std::fill(arr.begin(), arr.end(), 3.14);
  i += 100;
  std::cerr << i << "[KiB] Allocated in the stack" << std::endl;
  allocate_memory_on_stack(i);
}

int main() {
  allocate_memory_on_stack(0);
  return 0;
}