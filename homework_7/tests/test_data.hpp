// @file      test_data.hpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#ifndef TEST_DATA_HPP_
#define TEST_DATA_HPP_
#include <vector>

#include <opencv2/core/mat.hpp>

//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80
std::vector<cv::Mat> &GetDummyData();
cv::Mat GetAllFeatures();

//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80
cv::Mat Get18Kmeans();

//  dummy clustered data
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  40, 40, 40, 40, 40, 40, 40, 40, 40, 40;
//  60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
//  80, 80, 80, 80, 80, 80, 80, 80, 80, 80
cv::Mat Get5Kmeans();

// With values [0,2,4,6,8], the 3-kMea2s is [0, 3, 7]
//              ^  ^  ^
//              0  3  7
//  00, 00, 00, 00, 00, 00, 00, 00, 00, 00;
//  30, 30, 30, 30, 30, 30, 30, 30, 30, 30;
//  70, 70, 70, 70, 70, 70, 70, 70, 70, 70
cv::Mat Get3Kmeans();

// With values [0,2,4,6,8], the 3-kMea2s is [2, 7]
//                ^    ^
//  20, 20, 20, 20, 20, 20, 20, 20, 20, 20;
//  70, 70, 70, 70, 70, 70, 70, 70, 70, 70
cv::Mat Get2Kmeans();

#endif // TEST_DATA_HPP_
