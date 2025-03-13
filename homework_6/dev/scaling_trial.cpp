#include "homework_6.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

void display_image(const igg::Image &img, const std::string &window_name) {
  cv::Mat img_mat = cv::Mat(img.rows(), img.cols(), CV_8UC1,
                            const_cast<uint8_t *>(img.data().data()));
  cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
  cv::imshow(window_name, img_mat);
  cv::waitKey(0);
}

int main() {
  // load image
  // pgm file path
  std::string pgm_path_lena = "data/lena.ascii.pgm";
  // std::string pgm_path_dummy = "tests/data/dummy_file.pgm";

  // fill image from pgm
  igg::Image img;
  bool img_load_sucess = img.FillFromPgm(pgm_path_lena);
  if (!img_load_sucess) {
    std::cerr << "Error loading image from pgm file" << std::endl;
    return 1;
  }

  // original image
  display_image(img, "original");

  // downscale image
  img.DownScale(2);
  display_image(img, "downscaled");

  // upscale image
  img.UpScale(2);
  display_image(img, "upscaled");

  return 0;
}