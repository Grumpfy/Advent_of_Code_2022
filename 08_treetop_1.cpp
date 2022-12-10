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
  auto const grid_width = static_cast<size_t>(std::distance(input.begin(), ranges::find(input, '\n')));
  auto const grid_stride = grid_width + 1U;
  auto const grid_height = (input.size() + 1U) / grid_stride;
  auto height_at = [grid_stride, input](size_t x_pos, size_t y_pos) {
    return input.at(x_pos + y_pos * grid_stride);
  };
  auto set_bit = [grid_width](size_t x_pos, size_t y_pos, auto & bitset) {
    bitset.set(x_pos + y_pos * grid_width);
  };

  boost::dynamic_bitset<uint64_t> from_left(grid_width*grid_height);
  boost::dynamic_bitset<uint64_t> from_right(grid_width*grid_height);
  for (auto y_pos = size_t{}; y_pos < grid_height; ++y_pos) {
    auto max_height_from_left = '/';
    auto max_height_from_right = '/';
    for (auto x_pos = size_t{}; x_pos < grid_width; ++x_pos) {
      {
        auto const current_height_from_left = height_at(x_pos, y_pos);
        if (current_height_from_left > max_height_from_left) {
          set_bit(x_pos, y_pos, from_left);
        }
        max_height_from_left = std::max(max_height_from_left, current_height_from_left);
      }
      {
        auto const right_x_pos = grid_width - x_pos - 1;
        auto const current_height_from_right = height_at(right_x_pos, y_pos);
        if (current_height_from_right > max_height_from_right) {
          set_bit(right_x_pos, y_pos, from_right);
        }
        max_height_from_right = std::max(max_height_from_right, current_height_from_right);        
      }
    }
  }
  boost::dynamic_bitset<uint64_t> from_top(grid_width*grid_height);
  boost::dynamic_bitset<uint64_t> from_down(grid_width*grid_height);
  for (auto x_pos = size_t{}; x_pos < grid_width; ++x_pos) {
    auto max_height_from_top = '/';
    auto max_height_from_down = '/';
    for (auto y_pos = size_t{}; y_pos < grid_height; ++y_pos) {
      {
        auto const current_height_from_top = height_at(x_pos, y_pos);
        if (current_height_from_top > max_height_from_top) {
          set_bit(x_pos, y_pos, from_top);
        }
        max_height_from_top = std::max(max_height_from_top, current_height_from_top);
      }
      {
        auto const bottom_y_pos = grid_height - y_pos - 1;
        auto const current_height_from_down = height_at(x_pos, bottom_y_pos);
        if (current_height_from_down > max_height_from_down) {
          set_bit(x_pos, bottom_y_pos, from_down);
        }
        max_height_from_down = std::max(max_height_from_down, current_height_from_down);        
      }
    }
  }

  return int64_t((from_left | from_right | from_top | from_down).count());
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
