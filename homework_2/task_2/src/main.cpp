#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

int main(int argc, const char *argv[]) {
  // check for input arguemnts
  if (argc != 3) {
    std::cerr << "[Error] Usage: ./bin/task_2 <file1> <file2>" << std::endl;
    return EXIT_FAILURE;
  }
  // retreive input arguments
  std::string input1 = argv[1];
  std::string input2 = argv[2];

  // find index of '.' to slice string
  int idx1 = input1.find('.');
  int idx2 = input2.find('.');
  // std::cout << idx1 << std::endl;
  // std::cout << idx2 << std::endl;

  if (idx1 == -1 || idx2 == -1) {
    // Throw error if '.' not found
    std::cerr << "Error: Invalid input" << std::endl;
    return EXIT_FAILURE;

  } else {
    // extract file extensions
    std::string ext1 = input1.substr(idx1 + 1, input1.length() - 1);
    std::string ext2 = input2.substr(idx2 + 1, input2.length() - 1);
    //   std::cout << ext1 << std::endl;
    //   std::cout << ext2 << std::endl;

    try {
      // try converting to integer
      int num1 = std::stoi(input1.substr(0, idx1));
      int num2 = std::stoi(input2.substr(0, idx2));
      //   std::cout << num1 << std::endl;
      //   std::cout << num2 << std::endl;

      // conditions
      if (ext1 == "txt" && ext2 == "txt") {
        std::cout << (num1 + num2) / 2 << std::endl;
      } else if (ext1 == "png" && ext2 == "png") {
        std::cout << num1 + num2 << std::endl;
      } else if (ext1 == "txt" && ext2 == "png") {
        std::cout << num1 % num2 << std::endl;
      } else {
        // Abort if conditions not met
        std::cerr << "Error: Invalid input" << std::endl;
        return EXIT_FAILURE;
      }
    } catch (std::invalid_argument) {
      // Throw error if names are not integers
      std::cerr << "Error: Invalid input" << std::endl;
      return EXIT_FAILURE;
    }
  }
  // program executed succesfully
  return EXIT_SUCCESS;
}