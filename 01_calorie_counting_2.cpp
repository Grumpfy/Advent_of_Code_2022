#include "puzzle_input/01.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/all.hpp>

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

auto main() -> int {
  static constexpr auto nb_maximums = 3;
  auto max = absl::InlinedVector<int64_t, nb_maximums + 1>();
  max.emplace_back();
  for (auto [match, calories, next] : ctre::range<"(\\d+)|(\n\n)">(puzzle_input)) {
    if (calories) {
      max.back() += calories.to_number<int64_t>();
    } else {
      if (max.size() <= nb_maximums) {
        max.emplace_back();
      } else {
        std::sort(max.begin(), max.end(), std::greater<>{});
        max.back() = int64_t{};
      }
    }
  }
  std::sort(max.begin(), max.end(), std::greater<>{});
  max.pop_back();
  assert(max.size() == nb_maximums);

  fmt::print("The answer is: {}\n", ranges::fold_left(max, int64_t{}, std::plus<>{}));
  
  return 0;
}
