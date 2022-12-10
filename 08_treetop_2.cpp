#include "puzzle_input/08.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/lower_bound.hpp>
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/all.hpp>
#include <range/v3/view/filter.hpp>
#include <sys/_types/_int64_t.h>

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

auto solve(std::string_view input) -> int64_t {
  auto const grid_width =
      static_cast<size_t>(std::distance(input.begin(), ranges::find(input, '\n')));
  auto const grid_stride = grid_width + 1U;
  auto const grid_height = (input.size() + 1U) / grid_stride;
  auto height_at = [grid_stride, input](size_t x_pos, size_t y_pos) {
    return input.at(x_pos + y_pos * grid_stride);
  };

  auto max_scenic_score = int64_t{};
  for (auto y_pos = size_t{1}; y_pos < (grid_height - 1U); ++y_pos) {
    for (auto x_pos = size_t{1}; x_pos < (grid_width)-1U; ++x_pos) {
      auto const current_height = height_at(x_pos, y_pos);

      auto left_score = int64_t{};
      {
        auto left_pos = x_pos;
        while (--left_pos >= 0) {
          left_score++;
          if (height_at(left_pos, y_pos) >= current_height || left_pos == 0) {
            break;
          }
        }
      }

      auto right_score = int64_t{};
      {
        auto right_pos = x_pos;
        while (++right_pos < grid_width) {
          right_score++;
          if (height_at(right_pos, y_pos) >= current_height) {
            break;
          }
        }
      }

      auto top_score = int64_t{};
      {
        auto top_pos = y_pos;
        while (--top_pos >= 0) {
          top_score++;
          if (height_at(x_pos, top_pos) >= current_height || top_pos == 0) {
            break;
          }
        }
      }

      auto down_score = int64_t{};
      {
        auto down_pos = y_pos;
        while (++down_pos < grid_height) {
          down_score++;
          if (height_at(x_pos, down_pos) >= current_height) {
            break;
          }
        }
      }

      max_scenic_score =
          std::max(max_scenic_score, left_score * right_score * top_score * down_score);
    }
  }

  return max_scenic_score;
}

auto main() -> int {
  auto const start = std::chrono::high_resolution_clock::now();
  auto const answer = solve(puzzle_input);
  auto const end = std::chrono::high_resolution_clock::now();
  auto const elapsed = std::chrono::nanoseconds(end - start);

  fmt::print("The answer is: {}\n", answer);
  fmt::print("Computed in {}\n", elapsed);

  return 0;
}
