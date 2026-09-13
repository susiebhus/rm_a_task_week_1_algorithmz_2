#include "structuring_element.hpp"

#include <cstdlib>
#include <stdexcept>
#include <utility>

StructuringElement::StructuringElement(BinaryImage::Matrix mask) : mask_(std::move(mask)) {
  BinaryImage checked(mask_);
  if (checked.height() % 2 == 0 || checked.width() % 2 == 0) {
    throw std::invalid_argument("structuring element dimensions must be odd");
  }
}

std::size_t StructuringElement::height() const noexcept { return mask_.size(); }
std::size_t StructuringElement::width() const noexcept { return mask_.front().size(); }
std::size_t StructuringElement::anchor_row() const noexcept { return height() / 2; }
std::size_t StructuringElement::anchor_column() const noexcept { return width() / 2; }
BinaryImage::Pixel StructuringElement::at(const std::size_t row, const std::size_t column) const { return mask_.at(row).at(column); }

StructuringElement StructuringElement::square(const std::size_t size) {
  if (size == 0 || size % 2 == 0) throw std::invalid_argument("square size must be positive and odd");
  return StructuringElement(BinaryImage::Matrix(size, std::vector<BinaryImage::Pixel>(size, 1)));
}

StructuringElement StructuringElement::diamond(const std::size_t radius) {
  const auto size = radius * 2 + 1;
  BinaryImage::Matrix mask(size, std::vector<BinaryImage::Pixel>(size, 0));
  for (std::size_t row = 0; row < size; ++row) {
    for (std::size_t column = 0; column < size; ++column) {
      const auto row_distance = static_cast<std::size_t>(std::abs(static_cast<long long>(row) - static_cast<long long>(radius)));
      const auto column_distance = static_cast<std::size_t>(std::abs(static_cast<long long>(column) - static_cast<long long>(radius)));
      mask[row][column] = row_distance + column_distance <= radius ? 1 : 0;
    }
  }
  return StructuringElement(std::move(mask));
}

StructuringElement StructuringElement::cross(const std::size_t size) {
  if (size == 0 || size % 2 == 0) throw std::invalid_argument("cross size must be positive and odd");
  BinaryImage::Matrix mask(size, std::vector<BinaryImage::Pixel>(size, 0));
  const auto center = size / 2;
  for (std::size_t index = 0; index < size; ++index) {
    mask[center][index] = 1;
    mask[index][center] = 1;
  }
  return StructuringElement(std::move(mask));
}
