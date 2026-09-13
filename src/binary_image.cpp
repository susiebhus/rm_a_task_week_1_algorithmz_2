#include "binary_image.hpp"

#include <stdexcept>
#include <utility>

namespace {
void validate(const BinaryImage::Matrix& pixels) {
  if (pixels.empty() || pixels.front().empty()) {
    throw std::invalid_argument("binary image dimensions must be non-zero");
  }
  const auto image_width = pixels.front().size();
  for (const auto& row : pixels) {
    if (row.size() != image_width) throw std::invalid_argument("binary image rows must have equal width");
    for (const auto pixel : row) {
      if (pixel != 0 && pixel != 1) throw std::invalid_argument("binary image pixels must be 0 or 1");
    }
  }
}
}  // namespace

BinaryImage::BinaryImage(Matrix pixels) : pixels_(std::move(pixels)) { validate(pixels_); }

BinaryImage::BinaryImage(const std::size_t height, const std::size_t width, const Pixel value)
    : pixels_(height, std::vector<Pixel>(width, value)) {
  validate(pixels_);
}

std::size_t BinaryImage::height() const noexcept { return pixels_.size(); }
std::size_t BinaryImage::width() const noexcept { return pixels_.front().size(); }
BinaryImage::Pixel BinaryImage::at(const std::size_t row, const std::size_t column) const { return pixels_.at(row).at(column); }
void BinaryImage::set(const std::size_t row, const std::size_t column, const Pixel value) {
  if (value != 0 && value != 1) throw std::invalid_argument("binary image pixels must be 0 or 1");
  pixels_.at(row).at(column) = value;
}
const BinaryImage::Matrix& BinaryImage::pixels() const noexcept { return pixels_; }
