#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

class BinaryImage {
 public:
  using Pixel = std::uint8_t;
  using Matrix = std::vector<std::vector<Pixel>>;

  explicit BinaryImage(Matrix pixels);
  BinaryImage(std::size_t height, std::size_t width, Pixel value = 0);

  std::size_t height() const noexcept;
  std::size_t width() const noexcept;
  Pixel at(std::size_t row, std::size_t column) const;
  void set(std::size_t row, std::size_t column, Pixel value);
  const Matrix& pixels() const noexcept;

 private:
  Matrix pixels_;
};
