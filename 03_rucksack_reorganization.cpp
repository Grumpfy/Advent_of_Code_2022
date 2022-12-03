#include "puzzle_input/03.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
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

auto encode(std::string_view rucksack) -> std::pair<uint64_t, uint64_t> {
  auto pos = size_t{};
  auto mid = rucksack.size() / 2;
  auto compartment_1 = uint64_t{};
  for (; pos < mid; ++pos) {
    compartment_1 |= uint64_t{1} << index(rucksack[pos]);
  }
  auto compartment_2 = uint64_t{};
  for (; pos < rucksack.size(); ++pos) {
    compartment_2 |= uint64_t{1} << index(rucksack[pos]);
  }
  return std::make_pair(compartment_1, compartment_2);
}

auto main() -> int {
  auto sum = uint64_t{};
  for (auto [match, rucksack] : ctre::range<"([A-Za-z]+)">(puzzle_input)) {
    auto const [compartment_1, compartment_2] = encode(rucksack.to_view());
    auto const intersection = compartment_1 & compartment_2;
    auto const priority = std::countr_zero(intersection);
    sum += uint64_t(priority);
  }

  fmt::print("The answer is: {}\n", sum);

  return 0;
}
