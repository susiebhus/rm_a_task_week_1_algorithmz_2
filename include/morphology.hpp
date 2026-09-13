#pragma once

#include "binary_image.hpp"
#include "structuring_element.hpp"

class Morphology {
 public:
  // Pixels outside the source image are treated as background (0).
  static BinaryImage dilate(const BinaryImage& source, const StructuringElement& kernel);
  static BinaryImage erode(const BinaryImage& source, const StructuringElement& kernel);
};
