#include <iostream>
#include <opencv2/core.hpp>

#include "homework_9.h"

int main() {
    // get dictionary instance
    auto &dictionary = ipb::BowDictionary::GetInstance();
    // cv::Mat empty;

    auto histogram = ipb::Histogram(cv::Mat(), dictionary);
    std::cout << histogram.empty() << std::endl;
    std::cout << histogram.size() << std::endl;
    return 0;
}