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

void Histogram::WriteToCSV(const std::string &filename) {
    // Open the file using ofstream for writing
    std::ofstream file(filename);

    // Check if the file opened successfully
    if (file.is_open()) {
        // loop over vector and write values seperated by commas
        file << data_[0];
        for (int i = 1; i < data_.size(); i++) {
            file << ',' << data_[i];
        }
    } else {  // exit program on failure
        std::cerr << "Failed to open the file." << std::endl;
        exit(1);
    }
}

std::vector<int> split_string(std::string &s, const std::string &delimiter) {
    std::vector<int> data;
    size_t pos = 0;
    int token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = stoi(s.substr(0, pos));
        data.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    data.push_back(stoi(s));

    return data;
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