#include <absl/container/flat_hash_map.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/core.h>
#include <range/v3/all.hpp>
#include <sys/_types/_int64_t.h>

#include <string>
#include <string_view>
#include <vector>

#include "puzzle_input/01.h"

auto main() -> int {

  auto max = int64_t{};
  auto sum = int64_t{};
  for (auto [match, calories, next] : ctre::range<"(\\d+)|(\n\n)">(puzzle_input)) {
    if (calories) {
      sum += calories.to_number<int64_t>();
      max = std::max(max, sum);
    } else {
      sum = 0;
    }
  }

  fmt::print("The answer is: {}\n", max);

  return 0;
}
