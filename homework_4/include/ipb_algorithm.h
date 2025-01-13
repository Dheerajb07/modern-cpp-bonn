#ifndef IPB_ALGORITHM_H
#define IPB_ALGORITHM_H

#include "homework_4.h"

namespace ipb {

int accumulate(const ipb::named_vector<int> &named_vector);

int count(const ipb::named_vector<int> &named_vector, int num);

bool all_even(const ipb::named_vector<int> &named_vector);

void clamp(ipb::named_vector<int> &named_vector,int min, int max);

void fill(ipb::named_vector<int> &named_vector, int num);

bool find(ipb::named_vector<int> &named_vector, int num);

void print(ipb::named_vector<int> &named_vector);

void toupper(ipb::named_vector<int> &named_vector);

void sort(ipb::named_vector<int> &named_vector);

void rotate(ipb::named_vector<int> &named_vector, int pos);

void reverse(ipb::named_vector<int> &named_vector);

}
#endif