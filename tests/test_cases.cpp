#include "morphology.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {
using Matrix = BinaryImage::Matrix;

void expect_equal(const BinaryImage& actual, const Matrix& expected, const std::string& name) {
  if (actual.pixels() == expected) return;
  std::cerr << "FAIL: " << name << '\n';
  std::exit(EXIT_FAILURE);
}

void test_single_pixel() {
  const BinaryImage input({{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0}});
  expect_equal(Morphology::dilate(input, StructuringElement::square(5)),
               {{0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 0},
                {0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0}},
               "single pixel with a 5x5 square");
}

void test_small_square() {
  const BinaryImage input({{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0},
                           {0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0}});
  expect_equal(Morphology::dilate(input, StructuringElement::square(5)),
               {{1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 0},
                {1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 0},
                {0, 0, 0, 0, 0, 0, 0}},
               "small square dilation");
}

void test_edge_pixel() {
  const BinaryImage input({{1, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}});
  expect_equal(Morphology::dilate(input, StructuringElement::square(5)),
               {{1, 1, 1, 0, 0}, {1, 1, 1, 0, 0}, {1, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}},
               "edge pixel is clipped to image bounds");
}

void test_adjacent_regions_and_empty_image() {
  const BinaryImage regions({{0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0}});
  expect_equal(Morphology::dilate(regions, StructuringElement::cross(3)),
               {{0, 0, 1, 0, 1, 0, 0}, {0, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 0, 1, 0, 0}},
               "adjacent regions merge");
  const BinaryImage empty(4, 4);
  expect_equal(Morphology::dilate(empty, StructuringElement::square(5)),
               {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, "empty foreground remains empty");
}

void test_replaceable_kernels_and_erosion() {
  const BinaryImage single({{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}});
  expect_equal(Morphology::dilate(single, StructuringElement::diamond(2)),
               {{0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {1, 1, 1, 1, 1}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}},
               "diamond kernel produces dilation2 shape");
  const BinaryImage solid({{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}});
  expect_equal(Morphology::erode(solid, StructuringElement::square(3)),
               {{0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0}},
               "erosion contracts foreground at borders");
}
}  // namespace

int main() {
  test_single_pixel();
  test_small_square();
  test_edge_pixel();
  test_adjacent_regions_and_empty_image();
  test_replaceable_kernels_and_erosion();
  std::cout << "PASS: 6 morphology test scenarios\n";
}
