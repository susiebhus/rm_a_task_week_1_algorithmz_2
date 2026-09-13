#include "morphology.hpp"

#include <iostream>

namespace {
void print(const BinaryImage& image, const char* title) {
  std::cout << title << "\n";
  for (const auto& row : image.pixels()) {
    for (const auto pixel : row) std::cout << static_cast<int>(pixel) << ' ';
    std::cout << '\n';
  }
  std::cout << '\n';
}
}  // namespace

int main() {
  const BinaryImage input({
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
  });

  const auto square5 = StructuringElement::square(5);
  print(input, "input");
  print(Morphology::dilate(input, square5), "5x5 square dilation");
  print(Morphology::dilate(input, StructuringElement::diamond(2)), "dilation2: 5x5 diamond");
  print(Morphology::dilate(input, StructuringElement::cross(5)), "5x5 cross dilation");
  print(Morphology::erode(Morphology::dilate(input, square5), square5), "erosion after dilation");
}
