#include "puzzle_input/12.h"

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
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/all.hpp>
#include <range/v3/numeric/iota.hpp>
#include <range/v3/view/filter.hpp>
#include <sys/_types/_int64_t.h>

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

auto solve(std::string_view input) -> int64_t {
  auto const grid_width =
      static_cast<size_t>(std::distance(input.begin(), ranges::find(input, '\n')));
  auto const grid_stride = grid_width + 1U;
  auto const grid_height = (input.size() + 1U) / grid_stride;
  using GridPos = std::pair<size_t, size_t>;
  auto mark_at = [grid_stride, input](GridPos pos) {
    return input.at(pos.first + pos.second * grid_stride);
  };
  auto to_height = [](auto mark) -> int { return mark == 'S' ? int('a') : (mark == 'E' ? int('z') : int(mark)); };
  auto height_at = [mark_at, to_height](GridPos pos) { return to_height(mark_at(pos)); };
  auto get_index = [grid_width](GridPos pos) { return pos.first + pos.second * grid_width; };
  auto neighbors = [grid_width, grid_height](GridPos pos) -> absl::InlinedVector<GridPos, 4> {
    auto result = absl::InlinedVector<GridPos, 4>{};
    if (pos.first > 0) {
      result.push_back({pos.first - 1U, pos.second});
    }
    if (pos.second > 0) {
      result.push_back({pos.first, pos.second - 1U});
    }
    if (pos.first < (grid_width - 1U)) {
      result.push_back({pos.first + 1U, pos.second});
    }
    if (pos.second < (grid_height - 1U)) {
      result.push_back({pos.first, pos.second + 1U});
    }
    return result;
  };
  // auto prev = std::vector<std::pair<size_t, size_t>>(grid_width * grid_height);
  auto distance =
      std::vector<int64_t>(grid_width * grid_height, std::numeric_limits<int64_t>::max());
  struct QueueData {
    int64_t dist;
    GridPos pos;
    auto operator<(QueueData const &other) const -> bool { return dist > other.dist; }
  };
  auto pq = boost::heap::priority_queue<QueueData>();
  auto const start_index = size_t(std::distance(input.begin(), ranges::find(input, 'S')));
  auto const start_pos = GridPos{start_index%grid_stride, start_index/grid_stride};
  pq.push({0, start_pos});
  distance.at(get_index(start_pos)) = 0;

  auto end_pos = GridPos{};
  auto min_distance = int64_t{-1};
  while (!pq.empty()) {
    auto const min_node = pq.top();
    pq.pop();
    if (min_node.dist != distance.at(get_index(min_node.pos))) {
      continue;
    }    
    auto const min_node_mark = mark_at(min_node.pos);
    if (min_node_mark == 'E') {
      end_pos = min_node.pos;
      min_distance = min_node.dist;
      break;
    }
    auto const min_node_height = to_height(min_node_mark);
    for (auto const &neighbor : neighbors(min_node.pos)) {
      auto const neighbor_height = height_at(neighbor);
      if (neighbor_height > (min_node_height + 1)) {
        continue;
      }
      auto const new_distance = min_node.dist + 1U;
      auto const neighbor_index = get_index(neighbor);
      if (new_distance < distance.at(neighbor_index)) {
        distance.at(neighbor_index) = new_distance;
        // prev.at(neighbor_index) = min_node.pos;
        pq.push({new_distance, neighbor});
      }
    }
  }
  
  return min_distance;
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
