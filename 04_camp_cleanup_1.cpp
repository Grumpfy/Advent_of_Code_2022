#include "puzzle_input/04.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/all.hpp>

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
  auto total = 0;
  for (auto [match, begin_1, end_1, begin_2, end_2] :
       ctre::range<R"_((\d+)-(\d+),(\d+)-(\d+))_">(input)) {
    auto const interval_1 = std::make_pair(begin_1.to_number(), end_1.to_number());
    auto const interval_2 = std::make_pair(begin_2.to_number(), end_2.to_number());
    if ((interval_1.first >= interval_2.first && interval_1.second <= interval_2.second) ||
        (interval_1.first <= interval_2.first && interval_1.second >= interval_2.second)) {
      ++total;
    }
  }
  return total;
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
