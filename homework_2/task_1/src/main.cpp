#include <cstdlib>
#include <iostream>
#include <random>

int main() {
  bool flag = 0;
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 99);
  int rand = dist(rd);
  std::cout << "System has chosen a random number between 0-99" << std::endl;

  while (flag != 1) {
    // get user input
    std::cin.clear();
    int guess;
    std::cout << "Guess the number : ";
    std::cin >> guess;

    // check input validity
    if (std::cin.fail()) {
      std::cerr << "Error encountered, exiting..." << std::endl;
      return EXIT_FAILURE;
    } else {
      if (guess < 0 || guess > 99) {
        std::cerr << "[WARNING] : Number must be between 0 and 99" << std::endl;
        return EXIT_FAILURE;
      }
      // check input and guess
      if (guess == rand) {
        std::cout << "Your guess is correct!" << std::endl;
        flag = 1;
      } else if (guess < rand) {
        std::cout << "Your guess is less than the random number" << std::endl;
      } else {
        std::cout << "Your guess is greater than the random number"
                  << std::endl;
      }
    }
  }
  // exit program: SUCCESS if number gussed correctly
  std::cout << "The random number is " << rand << std::endl;
  return EXIT_SUCCESS;
}
