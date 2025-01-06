#include "image_browser.hpp"
#include <string>
#include <tuple>
#include <vector>

int main() {
  // title
  std::string title = "Dheeraj's Image Browser";

  // stylesheet path
  std::string stylesheet = "style.css";

  // vector of image paths
  std::vector<std::string> img_paths = {
      "data/000000.png", "data/000100.png", "data/000200.png",
      "data/000300.png", "data/000400.png", "data/000500.png",
      "data/000600.png", "data/000700.png", "data/000800.png"};
  // vector of scores
  std::vector<float> scores = {0.98,0.96,0.88,0.87,0.80,0.79,0.76,0.75,0.20};

  // init tuples with image path and score
  image_browser::ScoredImage img1 = std::make_tuple("data/000000.png", 0.98);
  image_browser::ScoredImage img2 = std::make_tuple("data/000100.png", 0.96);
  image_browser::ScoredImage img3 = std::make_tuple("data/000200.png", 0.88);
  image_browser::ScoredImage img4 = std::make_tuple("data/000300.png", 0.87);
  image_browser::ScoredImage img5 = std::make_tuple("data/000400.png", 0.80);
  image_browser::ScoredImage img6 = std::make_tuple("data/000500.png", 0.79);
  image_browser::ScoredImage img7 = std::make_tuple("data/000600.png", 0.76);
  image_browser::ScoredImage img8 = std::make_tuple("data/000700.png", 0.75);
  image_browser::ScoredImage img9 = std::make_tuple("data/000800.png", 0.20);

  // init vectors(rows) of ScoredImage tuples
  image_browser::ImageRow img_row1 = {img1, img2, img3};
  image_browser::ImageRow img_row2 = {img4, img5, img6};
  image_browser::ImageRow img_row3 = {img7, img8, img9};

  // init vector of ImageRows
  std::vector<image_browser::ImageRow> image_rows = {img_row1, img_row2,
                                                     img_row3};

  // create browser
  image_browser::CreateImageBrowser(title, stylesheet, image_rows);

  return 0;
}