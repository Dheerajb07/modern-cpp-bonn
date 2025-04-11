#include "homework_8.h"
#include <memory>
#include <string>

int main() {
  /*
   * PPM IO STRAT
   */
  // ppm file path
  std::string read_file_path = "data/pbmlib.ascii.ppm";
  std::string write_file_path = "data/write_pbmlib.ppm";

  // Read image from ppm file
  igg::Image img;
  img.SetIoStrategy(std::make_shared<igg::PpmIoStrategy>());
  img.ReadFromDisk(read_file_path);

  // Print Image Data
  std::cout << "Rows: " << img.rows() << ", "
            << "Cols: " << img.cols() << std::endl;
  std::cout << "Max Val: " << static_cast<int>(img.max_value()) << std::endl;
  std::cout << "Vector size: " << img.data().size() << std::endl;

  // Write to ppm file
  img.WriteToDisk(write_file_path);

  return 0;
}