#include "puzzle_input/02.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/all.hpp>

#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

enum class Shape { Rock = 0, Paper, Scissors };

[[nodiscard]] auto score(Shape shape) -> int64_t { return static_cast<int64_t>(shape) + 1U; }

[[nodiscard]] auto score(Shape other, Shape me) -> int64_t {
  static constexpr auto table =
      std::array<std::array<int, 3>, 3>{{{{3, 6, 0}}, {{0, 3, 6}}, {{6, 0, 3}}}};
  return score(me) + table.at(static_cast<size_t>(other)).at(static_cast<size_t>(me));
}

auto main() -> int {
  auto total = int64_t{};
  for (auto [match, other, me] : ctre::range<"([A-C]) ([X-Z])">(puzzle_input)) {
    total += score(Shape(other.view().at(0) - 'A'), Shape(me.view().at(0) - 'X'));
  }

  fmt::print("The answer is: {}\n", total);

  return 0;
}
