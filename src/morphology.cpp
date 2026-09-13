#include "morphology.hpp"

namespace {
bool is_foreground(const BinaryImage& image, const long long row, const long long column) {
  return row >= 0 && column >= 0 && row < static_cast<long long>(image.height()) &&
         column < static_cast<long long>(image.width()) &&
         image.at(static_cast<std::size_t>(row), static_cast<std::size_t>(column)) == 1;
}
}  // namespace

BinaryImage Morphology::dilate(const BinaryImage& source, const StructuringElement& kernel) {
  BinaryImage output(source.height(), source.width());
  for (std::size_t row = 0; row < source.height(); ++row) {
    for (std::size_t column = 0; column < source.width(); ++column) {
      bool overlaps_foreground = false;
      for (std::size_t kernel_row = 0; kernel_row < kernel.height() && !overlaps_foreground; ++kernel_row) {
        for (std::size_t kernel_column = 0; kernel_column < kernel.width(); ++kernel_column) {
          if (kernel.at(kernel_row, kernel_column) == 0) continue;
          const auto source_row = static_cast<long long>(row) + static_cast<long long>(kernel_row) - static_cast<long long>(kernel.anchor_row());
          const auto source_column = static_cast<long long>(column) + static_cast<long long>(kernel_column) - static_cast<long long>(kernel.anchor_column());
          if (is_foreground(source, source_row, source_column)) {
            overlaps_foreground = true;
            break;
          }
        }
      }
      output.set(row, column, overlaps_foreground ? 1 : 0);
    }
  }
  return output;
}

BinaryImage Morphology::erode(const BinaryImage& source, const StructuringElement& kernel) {
  BinaryImage output(source.height(), source.width());
  for (std::size_t row = 0; row < source.height(); ++row) {
    for (std::size_t column = 0; column < source.width(); ++column) {
      bool kernel_fits = true;
      for (std::size_t kernel_row = 0; kernel_row < kernel.height() && kernel_fits; ++kernel_row) {
        for (std::size_t kernel_column = 0; kernel_column < kernel.width(); ++kernel_column) {
          if (kernel.at(kernel_row, kernel_column) == 0) continue;
          const auto source_row = static_cast<long long>(row) + static_cast<long long>(kernel_row) - static_cast<long long>(kernel.anchor_row());
          const auto source_column = static_cast<long long>(column) + static_cast<long long>(kernel_column) - static_cast<long long>(kernel.anchor_column());
          if (!is_foreground(source, source_row, source_column)) {
            kernel_fits = false;
            break;
          }
        }
      }
      output.set(row, column, kernel_fits ? 1 : 0);
    }
  }
  return output;
}
