#include "puzzle_input/15.h"

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
#include <range/v3/algorithm/adjacent_find.hpp>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/lower_bound.hpp>
#include <range/v3/algorithm/minmax.hpp>
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/algorithm/unique.hpp>
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

using Pos2D = std::pair<int, int>;
struct Sensor {
  Pos2D pos;
  Pos2D closest_beacon;
};

auto solve(std::string_view input) -> int64_t {
  auto sensors = std::vector<Sensor>{};
  sensors.reserve(32); // NOLINT
  for (auto [match, sensor_x, sensor_y, beacon_x, beacon_y] :
       ctre::range<R"_(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))_">(
           input)) {
    sensors.push_back(
        {Pos2D{sensor_x.to_number(), sensor_y.to_number()},
         Pos2D{beacon_x.to_number(), beacon_y.to_number()}});
  }

  using Interval = Pos2D;
  auto intervals = std::vector<Interval>{};
  intervals.reserve(sensors.size());
  auto constexpr max_row = 4000000;
  for (auto row = 0; row <= max_row; ++row) {
    for (auto const &sensor : sensors) {
      auto const dist = std::abs(sensor.pos.first - sensor.closest_beacon.first) +
                        std::abs(sensor.pos.second - sensor.closest_beacon.second);
      auto const row_dist_y = std::abs(sensor.pos.second - row);
      auto const remaining_dist = dist - row_dist_y;
      if (remaining_dist >= 0) {
        intervals.emplace_back(
            sensor.pos.first - remaining_dist, sensor.pos.first + remaining_dist);
      }
    }
    if (intervals.empty()) {
      continue;
    }
    ranges::sort(intervals);
    auto previous_intervals_end = intervals.front().second;
    for (auto const &interval : intervals | ranges::views::drop(1)) {
      if (interval.first > (previous_intervals_end+1)) {
        return int64_t(previous_intervals_end + 1) * int64_t(max_row) + int64_t(row);
      }
      previous_intervals_end = std::max(previous_intervals_end, interval.second);
    }
    intervals.clear();
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
