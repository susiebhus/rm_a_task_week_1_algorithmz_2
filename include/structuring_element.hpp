#pragma once

#include "binary_image.hpp"

class StructuringElement {
 public:
  explicit StructuringElement(BinaryImage::Matrix mask);

  std::size_t height() const noexcept;
  std::size_t width() const noexcept;
  std::size_t anchor_row() const noexcept;
  std::size_t anchor_column() const noexcept;
  BinaryImage::Pixel at(std::size_t row, std::size_t column) const;

  static StructuringElement square(std::size_t size);
  static StructuringElement diamond(std::size_t radius);
  static StructuringElement cross(std::size_t size);

 private:
  BinaryImage::Matrix mask_;
};
