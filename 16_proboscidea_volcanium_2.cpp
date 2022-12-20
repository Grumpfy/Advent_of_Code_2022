#include "puzzle_input/16.h"

#include <_types/_uint16_t.h>
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
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/lower_bound.hpp>
#include <range/v3/algorithm/minmax.hpp>
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/algorithm/permutation.hpp>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/algorithm/unique.hpp>
#include <range/v3/all.hpp>
#include <range/v3/iterator/insert_iterators.hpp>
#include <range/v3/numeric/iota.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/take.hpp>
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

struct Graph {
  static inline constexpr auto max_nodes = size_t(60);
  static inline constexpr auto max_neighbours = size_t(5);
  using FlowRates = std::vector<int>;
  using NodeIndices = absl::flat_hash_map<std::string_view, size_t>;
  using Neighbours = std::vector<absl::InlinedVector<size_t, max_neighbours>>;
  using DistancesMatrix = std::array<std::array<int, max_nodes>, max_nodes>;

  explicit Graph(std::string_view input) {
    node_index.reserve(max_nodes);
    node_flow_rate.reserve(max_nodes);
    neighbours.reserve(max_nodes);
    // parse input
    for (auto [match, valve_name, flow_rate, connections] :
         ctre::range<R"_(Valve (\w+) has flow rate=(\d+); tunnels? leads? to valves? ([A-Z ,]+))_">(
             input)) {
      auto const index =
          node_index.try_emplace(valve_name.to_view(), node_index.size()).first->second;
      if (node_flow_rate.size() <= index) {
        node_flow_rate.resize(index + 1);
        neighbours.resize(index + 1);
      }
      node_flow_rate.at(index) = flow_rate.to_number();
      for (auto [_, neighbour] : ctre::range<R"_(([A-Z]+))_">(connections.to_view())) {
        auto const neighbour_index =
            node_index.try_emplace(neighbour.to_view(), node_index.size()).first->second;
        neighbours.at(index).push_back(neighbour_index);
      }
    }
    // fill distance matrix
    // https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
    for (auto &line : dist) {
      line.fill(std::numeric_limits<int>::max()/2);
    }
    for (auto i = size_t{}; i < dist.size(); ++i) {
      dist[i][i] = 0;  // NOLINT
    }
    for (auto node = size_t{}; node < neighbours.size(); ++node) {
      for (auto neighbour : neighbours.at(node)) {
        dist[node][neighbour] = 1;  // NOLINT
        dist[neighbour][node] = 1;  // NOLINT
      }
    }
    for (auto k = size_t{}; k < dist.size(); ++k) {
      for (auto i = size_t{}; i < dist.size(); ++i) {
        for (auto j = size_t{}; j < dist.size(); ++j) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);  // NOLINT
        }
      }
    }
  }

  NodeIndices node_index;
  FlowRates node_flow_rate;
  Neighbours neighbours;
  DistancesMatrix dist = {};
};

static inline constexpr auto expected_valve_count = size_t{15};
using ValveIndices = absl::InlinedVector<size_t, expected_valve_count>;

auto solve(Graph const &g, std::string_view start_node, int max_time, ValveIndices const &valves)
    -> int {
  // https://en.wikipedia.org/wiki/Branch_and_bound
  struct State {
    size_t current_node_index;
    int remaining_time;
    ValveIndices remaining_valves;
    int pressure_released;
  };

  auto initial_state = State{g.node_index.at(start_node), max_time, valves, 0};

  auto evaluate_in_valve_order = [&g](State const &state) {
    auto score = 0;
    auto current_node = state.current_node_index;
    auto remaining_time = state.remaining_time;
    for (auto valve : state.remaining_valves) {
      remaining_time = remaining_time - g.dist[current_node][valve] - 1;  // NOLINT
      score += std::max(0, remaining_time * g.node_flow_rate.at(valve));
      current_node = valve;
    }
    return score;
  };

  auto upper_bound = [&g](State const &state) -> int {
    auto max = 0;
    for (auto valve : state.remaining_valves) {
      max += std::max(
          0,
          g.node_flow_rate.at(valve) *
              (state.remaining_time - g.dist.at(state.current_node_index).at(valve) - 1));
    }
    return state.pressure_released + max;
  };

  auto states = std::vector<State>{};
  states.reserve(10000);  // NOLINT
  states.push_back(initial_state);

  auto max_presure = evaluate_in_valve_order(initial_state);

  while (!states.empty()) {
    auto const state = states.back();
    states.pop_back();
    if (upper_bound(state) < max_presure) {
      continue;
    }
    for (auto valve : state.remaining_valves) {
      auto const remaining_time =
          state.remaining_time - g.dist[state.current_node_index][valve] - 1;  // NOLINT
      if (remaining_time < 0) {
        max_presure = std::max(max_presure, state.pressure_released);
        continue;
      }
      auto child_state = State{
          valve,
          remaining_time,
          {},
          state.pressure_released + remaining_time * g.node_flow_rate.at(valve)};
      ranges::copy(
          state.remaining_valves |
              ranges::views::filter([valve](auto index) { return index != valve; }),
          ranges::back_inserter(child_state.remaining_valves));
      if (child_state.remaining_valves.empty()) {
        max_presure = std::max(max_presure, child_state.pressure_released);
      } else if (upper_bound(child_state) > max_presure) {
        max_presure = std::max(max_presure, evaluate_in_valve_order(child_state));
        states.push_back(std::move(child_state));
      }
    }
  }
  return max_presure;
}

auto solve(std::string_view input) -> int64_t {
  auto const g = Graph(input);
  auto constexpr max_time = 26;
  auto valves = ValveIndices{};
  ranges::copy(
      ranges::views::iota(size_t(0), g.node_index.size()) |
          ranges::views::filter([&g](auto index) { return g.node_flow_rate.at(index) > 0; }),
      ranges::back_inserter(valves));

  auto const max_part = size_t{1U<<valves.size()};
  auto scores = std::vector<int>{};
  scores.reserve(max_part);
  for (auto part = size_t{}; part < max_part; ++part) {
    auto subset = ValveIndices{};
    auto index = size_t{};
    auto compressed_indices = part;
    while (compressed_indices != 0) {
      if ((compressed_indices & 1U) != 0) {
        subset.push_back(valves.at(index));
      }
      compressed_indices >>= 1U;
      ++index;
      auto const trailing_zero = size_t(std::countr_zero(compressed_indices));
      if (trailing_zero != 0) {
        compressed_indices >>= trailing_zero;
        index += trailing_zero;
      }
    }
    scores.push_back(solve(g, "AA", max_time, subset));
  }

  auto max_presure_released = 0;
  for (auto part = size_t{}; part < max_part; ++part) {
    auto const complement = ~part & (max_part-1);
    max_presure_released = std::max(max_presure_released, scores.at(part)+scores.at(complement));
  }
  
  return max_presure_released;
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
