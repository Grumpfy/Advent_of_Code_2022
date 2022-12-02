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
enum class Outcome { Lose = 0, Draw, Win };

[[nodiscard]] auto score(Shape shape) -> int64_t { return static_cast<int64_t>(shape) + 1U; }
[[nodiscard]] auto score(Outcome outcome) -> int64_t { return static_cast<int64_t>(outcome) * 3U; }
[[nodiscard]] auto my_shape(Shape other, Outcome outcome) -> Shape {
  static constexpr auto table =
      std::array<std::array<int, 3>, 3>{{{{2, 0, 1}}, {{0, 1, 2}}, {{1, 2, 0}}}};
  return Shape(table.at(static_cast<size_t>(other)).at(static_cast<size_t>(outcome)));
}

auto main() -> int {
  auto total = int64_t{};
  for (auto [match, other_token, outcome_token] : ctre::range<"([A-C]) ([X-Z])">(puzzle_input)) {
    auto const outcome = Outcome(outcome_token.view().at(0) - 'X');
    auto const other_shape = Shape(other_token.view().at(0) - 'A');
    total += score(outcome) + score(my_shape(other_shape, outcome));
  }

  fmt::print("The answer is: {}\n", total);

  return 0;
}
