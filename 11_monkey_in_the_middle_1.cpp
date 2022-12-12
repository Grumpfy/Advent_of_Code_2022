#include "puzzle_input/11.h"

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
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/slice.hpp>
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

#include "monkey_parser.h"

auto solve(std::string_view input) -> int64_t {
  auto monkeys = parse_monkeys(input);

  static constexpr auto nb_rounds = 20;
  for (auto i=0; i<nb_rounds; ++i) {
    for (auto & monkey : monkeys) {
      for (auto item : monkey.items) {
        item = monkey.priority_update(item) / 3;
        if ((item % monkey.test_value) == 0) {
          monkeys.at(monkey.target_if_true).items.push_back(item);
        } else {
          monkeys.at(monkey.target_if_false).items.push_back(item);
        }
      }
      monkey.inspected_items += int64_t(monkey.items.size());
      monkey.items.clear();
    } 
  }

  ranges::sort(monkeys, std::greater<>{}, [](auto const &monkey){return monkey.inspected_items;});
  
  return monkeys[0].inspected_items * monkeys[1].inspected_items;
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
