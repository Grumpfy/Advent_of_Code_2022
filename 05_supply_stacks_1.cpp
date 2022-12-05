#include "puzzle_input/05.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/all.hpp>

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

auto solve(std::string_view input) -> std::string {
  static constexpr auto stack_height = std::size_t(128);
  auto stacks = std::array<absl::InlinedVector<char, stack_height>, stacks_number>{};
  {
    auto stack_id = size_t{};
    for (auto [match, spaces, crate_id] : ctre::range<R"_((    )|\[([A-Z])\])_">(input)) {
      if (crate_id) {
        stacks.at(stack_id).push_back(crate_id.to_view().at(0));
      }
      stack_id = (stack_id + 1U) % stacks_number;
    }
    for (auto& stack : stacks) {
      ranges::reverse(stack);
    }
  }

  for (auto [match, crate_number, src_stack, dst_stack] :
       ctre::range<R"_(move (\d+) from (\d) to (\d))_">(input)) {
    auto const src = src_stack.to_number<size_t>() - 1U;
    auto const dst = dst_stack.to_number<size_t>() - 1U;
    for (auto crate_count = 0, end = crate_number.to_number(); crate_count < end; ++crate_count) {
      stacks.at(dst).push_back(stacks.at(src).back());
      stacks.at(src).pop_back();
    }
  }

  auto result = std::string{};
  for (auto const& stack : stacks) {
    result.push_back(stack.back());
  }

  return result;
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
