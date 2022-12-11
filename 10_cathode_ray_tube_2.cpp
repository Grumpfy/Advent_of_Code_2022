#include "puzzle_input/10.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/all.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/slice.hpp>
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

auto solve(std::string_view input) -> int {
  auto x_register = 1;
  auto cycle = 0;
  static constexpr auto crt_width = 40;
  static constexpr auto crt_height = 6;
  auto crt = std::array<char, size_t(crt_width * crt_height)>{};
  crt.fill(' ');
  for (auto [match, noop, addx] : ctre::range<R"_((noop)|addx (-?\d+))_">(input)) {
    auto const op_diration = addx ? 2 : 1;
    for (auto i=0; i<op_diration; ++i) {
      auto const line_pos = cycle % crt_width;
      if (line_pos >= x_register - 1 && line_pos <= x_register + 1) {
        crt.at(size_t(cycle)) = '#';
      }
      ++cycle;
    }
    if (addx) {
      x_register += addx.to_number();
    }
  }

  for (auto const & interval : crt | ranges::views::chunk(40)) {
    fmt::print("{}\n", fmt::join(interval,"")); 
  }
  
  return x_register;
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
