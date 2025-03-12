#include "homework_6.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

void display_image(const igg::Image &img, const std::string &window_name) {
  cv::Mat img_mat = cv::Mat(img.rows(), img.cols(), CV_8UC1,
                            const_cast<uint8_t *>(img.data().data()));
  cv::namedWindow("lena", cv::WINDOW_AUTOSIZE);
  cv::imshow("lena", img_mat);
  cv::waitKey(0);
}

int main() {
  // pgm file path
  std::string pgm_path = "data/lena.ascii.pgm";
  // fill image from pgm
  igg::Image img;
  bool img_load_sucess = img.FillFromPgm(pgm_path);
  if (!img_load_sucess) {
    std::cerr << "Error loading image from pgm file" << std::endl;
    return 1;
  }

  // print image data
  std::cout << img.rows() << std::endl;
  std::cout << img.cols() << std::endl;
  std::cout << int(img.max_value()) << std::endl;
  std::cout << int(img.at(0, 0)) << std::endl;

  // show image
  display_image(img, "lena");
  // write image to pgm file
  img.WriteToPgm("bin/lena_test_write.ascii.pgm");

  return 0;
}