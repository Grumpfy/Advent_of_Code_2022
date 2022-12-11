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

auto solve(std::string_view input) -> int {
  auto x_register = 1;
  auto cycle = 0;
  static constexpr auto offset = 20;
  static constexpr auto period = 40;
  auto interval_id = 0;
  auto signal_strength = 0;
  for (auto [match, noop, addx] : ctre::range<R"_((noop)|addx (-?\d+))_">(input)) {
    cycle += addx ? 2 : 1;
    auto const new_interval_id = (cycle + offset) / period; 
    if (new_interval_id != interval_id) {
      signal_strength += (interval_id * period + offset) * x_register;
      interval_id = new_interval_id;
    }
    if (addx) {
      x_register += addx.to_number();
    }
  }

  return signal_strength;
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
