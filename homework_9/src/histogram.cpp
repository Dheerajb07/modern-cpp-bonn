#include "histogram.hpp"

#include <fstream>
#include <iostream>
// #include <string>
// #include <vector>

#include "histogram_utils.hpp"

namespace ipb {

Histogram::Histogram(const cv::Mat &descriptors,
                     const BowDictionary &dictionary) {
    compute(descriptors, dictionary);
}

void Histogram::compute(const cv::Mat &descriptors,
                        const BowDictionary &dictionary) {
    if (!descriptors.empty() || !dictionary.empty()) {
        // if either descriptors of dictionary is empty exit function
        return;
    }

    // Init vector
    this->data_.resize(dictionary.size(), 0);

    const cv::Mat &vocab = dictionary.vocabulary();
    // Iterate over descriptors.
    for (int i = 0; i < descriptors.rows; i++) {
        // For each descriptor find the closest word in the dictionary
        std::vector<float> dist = L2distance(descriptors.row(i), vocab);
        // get nearest dist idx
        int min_idx = argminDist(dist);
        // Increment the count in histogram vector
        this->data_[i] += 1;
    }
}

std::ostream &operator<<(std::ostream &os, const Histogram &hist) {
    os << hist[0];
    for (int i = 1; i < hist.size(); i++) {
        os << ", " << hist[i];
    }
    return os;
}

void Histogram::WriteToCSV(const std::string &filename) {
    // Open the file using ofstream for writing
    std::ofstream file(filename);

    // Check if the file opened successfully
    if (file.is_open()) {
        // loop over vector and write values seperated by commas
        file << this->data_[0];
        for (int i = 1; i < this->data_.size(); i++) {
            file << ',' << this->data_[i];
        }
    } else {  // exit program on failure
        std::cerr << "Failed to open the file." << std::endl;
        exit(1);
    }
}

Histogram Histogram::ReadFromCSV(const std::string &filename) {
    // Open the file using ifstream for reading
    std::ifstream file(filename);
    // Check if the file opened successfully
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        std::vector<int> data = split_string(line, ",");
        Histogram hist(data);
        return hist;
    } else {  // exit program on failure
        std::cerr << "Failed to open the file." << std::endl;
        exit(1);
    }
}

}  // namespace ipb