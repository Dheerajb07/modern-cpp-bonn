#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdint>

namespace igg {

class Pixel {
public:
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  Pixel(){};
  Pixel(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b){};
};

} // namespace igg
#endif