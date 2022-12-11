#include "puzzle_input/09.h"

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

using Position = std::pair<int, int>;

auto translated(Position const &pos, Position const &v) -> Position {
  return {pos.first + v.first, pos.second + v.second};
}

auto offset(Position const &from, Position const &to) -> Position {
  return {to.first - from.first, to.second - from.second};
}

auto catch_head(Position const &head, Position const &head_to_tail) -> Position {
  return {head.first + head_to_tail.first / 2, head.second + head_to_tail.second / 2};
}

auto l_inf(Position const &vect) -> int {
  return std::max(std::abs(vect.first), std::abs(vect.second));
}

auto solve(std::string_view input) -> int64_t {
  static constexpr auto rope_length = size_t{10};
  static constexpr auto tail_pos = size_t{9};
  auto rope = std::array<Position, rope_length>{};
  rope.fill(Position{0,0});
  auto visited_pos = absl::flat_hash_set<Position>{};
  visited_pos.insert(rope[tail_pos]);
  for (auto [match, direction_, steps_] : ctre::range<R"_(([LRUD]) (\d+))_">(input)) {
    auto direction = Position{};
    switch (*direction_.data()) {
      case 'L':
        direction = Position{-1, 0};
        break;
      case 'R':
        direction = Position{1, 0};
        break;
      case 'U':
        direction = Position{0, 1};
        break;
      case 'D':
        direction = Position{0, -1};
        break;
    }
    auto steps = steps_.to_number();
    for (auto i = 0; i < steps; ++i) {
      rope[0] = translated(rope[0], direction);
      for (auto k=size_t{}; k<tail_pos; ++k) {
        auto head_to_tail = offset(rope[k], rope[k+1]);
        if (l_inf(head_to_tail) > 1) {
          rope[k+1] = catch_head(rope[k], head_to_tail);
        }
      }
      visited_pos.insert(rope[tail_pos]);
    }
  }

  return int64_t(visited_pos.size());
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
