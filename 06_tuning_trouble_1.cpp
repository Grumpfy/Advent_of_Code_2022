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

template <typename Dst, typename Src>
[[nodiscard]] auto bit_cast(Src const & src) -> Dst {
  static_assert(sizeof(Src) == sizeof(Dst));
  auto dst = Dst{};
  std::memcpy(&dst, &src, sizeof(Dst));
  return dst;
}

auto solve(std::string_view input) -> int64_t {
  auto window = uint32_t{};
  auto const * current_char = input.begin();
  static constexpr auto char_size = 8U;
  for (auto i = 0; i<3; ++i) {
    window = (window << char_size) | static_cast<uint32_t>(*current_char);
    std::advance(current_char,1);
  }
  while (current_char != input.end()) {
    window = (window << char_size) | static_cast<uint32_t>(*current_char);
    auto as_bytes = bit_cast<std::array<char, 4>>(window);
    ranges::sort(as_bytes);
    if (ranges::adjacent_find(as_bytes) == as_bytes.end()) {
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
