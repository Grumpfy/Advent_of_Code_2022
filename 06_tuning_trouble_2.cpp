#include "puzzle_input/06.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/adjacent_find.hpp>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/all.hpp>

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

template <size_t N>
struct CircularBuffer {
  std::array<char, N> buffer = {};
  size_t back_index = 0;

  auto push_back(char value) noexcept -> char {
    back_index = (back_index + 1) % N;
    return std::exchange(buffer.at(back_index), value);
  }
};

auto solve(std::string_view input) -> int64_t {
  auto const * current_char = input.begin();
  static constexpr auto marker_size = size_t{14U};
  auto circular_buffer = CircularBuffer<marker_size>{};
  for (auto i = 0U; i<marker_size; ++i) {
    circular_buffer.push_back(*current_char);
    std::advance(current_char,1);
  }
  while (current_char != input.end()) {
    circular_buffer.push_back(*current_char);
    auto chars = circular_buffer.buffer;
    // most likely good enough for 14 chars 
    ranges::sort(chars);
    if (ranges::adjacent_find(chars) == chars.end()) {
      break;
    }
    std::advance(current_char,1);
  }
  return std::distance(input.begin(), current_char) + 1;
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
