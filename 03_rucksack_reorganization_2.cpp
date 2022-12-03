#include "puzzle_input/03.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
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

auto index(char item) -> size_t {
  static constexpr auto upper_offset = size_t{27};
  if (item <= 'Z') {
    return size_t(item - 'A') + upper_offset;
  }
  static constexpr auto lower_offset = size_t{1};
  return size_t(item - 'a') + lower_offset;
}

auto encode(std::string_view rucksack) -> uint64_t {
  auto content = uint64_t{};
  for (auto item : rucksack) {
    content |= uint64_t{1} << index(item);
  }
  return content;
}

auto main() -> int {
  auto sum = uint64_t{};
  auto group = absl::InlinedVector<uint64_t, 3>{};
  static constexpr auto group_size = size_t{3};
  for (auto [match, rucksack] : ctre::range<"([A-Za-z]+)">(puzzle_input)) {
    group.push_back(encode(rucksack.to_view()));
    if (group.size() == group_size) {
      auto const intersection = ranges::fold_left(group, ~uint64_t{}, std::bit_and<>{});
      auto const priority = std::countr_zero(intersection);
      sum += uint64_t(priority);
      group.clear();
    }
  }

  fmt::print("The answer is: {}\n", sum);

  return 0;
}
