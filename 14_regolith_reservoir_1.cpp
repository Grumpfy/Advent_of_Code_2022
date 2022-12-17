#include "puzzle_input/14.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/heap/priority_queue.hpp>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/lower_bound.hpp>
#include <range/v3/algorithm/minmax.hpp>
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/all.hpp>
#include <range/v3/numeric/iota.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/transform.hpp>
#include <sys/_types/_int64_t.h>

#include <array>
#include <bit>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iterator>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

auto solve(std::string_view input) -> int64_t {
  using Pos2D = std::pair<int, int>;
  auto rocks = std::vector<std::vector<Pos2D>>{};
  rocks.reserve(150);  // NOLINT
  rocks.emplace_back();
  for (auto [match, x, y, next] : ctre::range<R"_((\d+),(\d+)|(\n))_">(input)) {
    if (next) {
      rocks.emplace_back();
      rocks.back().reserve(40);  // NOLINT
    } else {
      rocks.back().emplace_back(x.to_number(), y.to_number());
    }
  }

  auto const [min_x, max_x] = ranges::minmax(
      rocks | ranges::views::join | ranges::views::transform(&Pos2D::first));
  auto const [_, max_y] = ranges::minmax(
      rocks | ranges::views::join | ranges::views::transform(&Pos2D::second));
  auto const min_y = 0;

  auto const x_offset = -min_x;
  auto const y_offset = -min_y;
  auto const width = max_x - min_x + 1;
  auto const height = max_y - min_y + 1;
  auto const sand_emitter_pos = Pos2D{500,0};
  auto index = [&, min_x=min_x, max_x=max_x, max_y=max_y](Pos2D const &pos) -> std::optional<size_t> {
    if (pos.first < min_x || pos.first > max_x || pos.second < min_y || pos.second > max_y) {
      return std::nullopt;
    }
    return static_cast<size_t>(pos.first + x_offset + width * (pos.second + y_offset)); // NOLINT
  };

  auto map = std::vector<char>(size_t(width * height), ' ');
  map.at(*index(sand_emitter_pos)) = '+';
  for (auto const &rock : rocks) {
    auto from = rock.front();
    for (auto to : rock | ranges::views::drop(1)) {
      if (from.first == to.first) {
        auto const x = from.first;
        auto const dy = (from.second > to.second) ? -1 : 1;
        for (auto y = from.second, end = to.second + dy; y!=end; y += dy) {
          map.at(*index({x,y})) = '#';
        }
      } else {
        assert(from.second == to.second);
        auto const y = from.second;
        auto const dx = (from.first > to.first) ? -1 : 1;
        for (auto x = from.first, end = to.first + dx; x!=end; x += dx) {
          map.at(*index({x,y})) = '#';
        }
      }
      from = to;
    }
  }

  [[maybe_unused]] auto print_map = [&map, width]{
    for (auto const & line : map | ranges::views::chunk(width)) {
      fmt::print("{}\n", fmt::join(line,"")); 
    }
  };
  
  auto sand_counter = int64_t{};
  while (true) {
    auto sand_pos = sand_emitter_pos;
    auto free_slot_found = true;
    while (free_slot_found) {
      free_slot_found = false;
      for (auto const &dir : {Pos2D{0,1}, Pos2D{-1,1}, Pos2D{1,1}}) {
        auto const down = Pos2D{sand_pos.first + dir.first, sand_pos.second + dir.second};
        auto const down_index = index(down);
        if (!down_index) {
          // print_map();
          return sand_counter;
        }
        if (map.at(*down_index) == ' ') {
          sand_pos = down;
          free_slot_found = true;
          break;
        }
      }
    }
    map.at(*index(sand_pos)) = 'o';
    ++sand_counter;
  }

  return -1;
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
