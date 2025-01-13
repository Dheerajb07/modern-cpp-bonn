#include "ipb_algorithm.h"
#include "homework_4.h"
#include <algorithm>
#include <numeric>

int ipb::accumulate(const ipb::named_vector<int> &v) {
  int sum = std::accumulate(v.vector().begin(),
                            v.vector().end(), 0);
  return sum;
}

int ipb::count(const ipb::named_vector<int> &v, int num) {
  int count = std::count(v.vector().begin(),
                         v.vector().end(), num);
  return count;
};

bool all_even(const ipb::named_vector<int> &v) {
  for (auto m : v.vector()) {
    if (m % 2 != 0) {
      return false;
    };
  }
  return true;
};

void clamp(ipb::named_vector<int> &v, int min, int max){
    std::vector<int> v_temp = v.vector();
    for(int i=0;i<v_temp.size();i++){
        if(v_temp[i] < min){
            v_temp[i] = min;
        }
        else if (v_temp[i] > max) {
            v_temp[i] = max;
        }
    }
    v.set_vector(v_temp);
};
void fill(ipb::named_vector<int> &named_vector, int num);

bool find(ipb::named_vector<int> &named_vector, int num);

void print(ipb::named_vector<int> &named_vector);

void toupper(ipb::named_vector<int> &named_vector);

void sort(ipb::named_vector<int> &named_vector);

void rotate(ipb::named_vector<int> &named_vector, int pos);

void reverse(ipb::named_vector<int> &named_vector);
