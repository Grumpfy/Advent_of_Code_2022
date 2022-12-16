#include "puzzle_input/13.h"

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
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

auto is_number(char c) -> bool {
  return c >= '0' && c <= '9';
}

[[nodiscard]] auto compare(std::string_view packet_1, std::string_view packet_2) -> bool {
  auto const * p1 = packet_1.begin();
  auto const * p2 = packet_2.begin();
  auto extra_eol_1 = 0;
  auto extra_eol_2 = 0;
  while (p1 != packet_1.end() && p2 != packet_2.end()) {
    auto const tok1 = (extra_eol_1 != 0 && !is_number(*p1)) ? ']' : *p1;
    auto const tok2 = (extra_eol_2 != 0 && !is_number(*p2)) ? ']' : *p2;
    if (tok1 == tok2 && !is_number(tok1)) {
      if (extra_eol_1 == 0) {std::advance(p1, 1);} else {--extra_eol_1;}
      if (extra_eol_2 == 0) {std::advance(p2, 1);} else {--extra_eol_2;}
      continue;
    }
    if (tok1 == ']') {
      return true;
    }
    if (tok2 == ']') {
      return false;
    }
    if (tok1 == '[') {
      assert(is_number(tok2));
      ++extra_eol_2;
      std::advance(p1, 1);
      continue;
    }
    if (tok2 == '[') {
      assert(is_number(tok1));
      ++extra_eol_1;
      std::advance(p2, 1);
      continue;
    }
    auto v1 = 0;
    p1 = std::from_chars(p1, packet_1.end(), v1).ptr;
    auto v2 = 0;
    p2 = std::from_chars(p2, packet_2.end(), v2).ptr;
    if (v1 == v2) {
      continue;
    }
    return v1 < v2;
  }
  return false;
}

auto solve(std::string_view input) -> int64_t {
  auto sum = int64_t{};
  auto index = int64_t{};
  auto const * current_pos = input.begin();
  while (true) {
    ++index;
    auto const * packet_1_begin = current_pos;
    auto const * packet_1_end = std::find(packet_1_begin, input.end(), '\n');
    auto const * packet_2_begin = std::next(packet_1_end);
    auto const * packet_2_end = std::find(packet_2_begin, input.end(), '\n');
    
    auto const packet_1 = std::string_view(packet_1_begin, size_t(std::distance(packet_1_begin, packet_1_end)));
    auto const packet_2 = std::string_view(packet_2_begin, size_t(std::distance(packet_2_begin, packet_2_end)));
    if (compare(packet_1, packet_2)) {
      sum += index;
    }
    if (packet_2_end == input.end()) {
      break;
    }
    current_pos = std::next(packet_2_end, 2);
  }
  
  return sum;
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
