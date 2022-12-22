#include "puzzle_input/17.h"

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
#include <range/v3/algorithm/none_of.hpp>
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
#include <range/v3/view/reverse.hpp>
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

using Sprite = absl::InlinedVector<uint8_t, 4>;
using Chamber = std::vector<uint8_t>;

auto shift(char dir, Sprite & sprite) -> bool {
  auto const left_border  = uint8_t{0b10000000};
  auto const right_border = uint8_t{0b00000010};
  if (dir == '>') {
    if (ranges::any_of(sprite, [right_border](auto line){return (line & right_border) != 0;})) {
      return false;
    }
    for (auto & line : sprite) {
      line >>= 1U;
    }
    return true;
  }
  assert(dir == '<');
  if (ranges::any_of(sprite, [left_border](auto line){return (line & left_border) != 0;})) {
    return false;
  }
  for (auto & line : sprite) {
    line <<= 1U;
  }
  return true;
}

auto collision(Sprite const &sprite, size_t sprite_height_pos, Chamber const &chamber) -> bool {
  for (auto line : sprite) {
    if ((chamber.at(sprite_height_pos++) & line) != 0) {
      return true;
    }
  }
  return false;
}

auto draw(Sprite const &sprite, size_t sprite_height_pos, Chamber &chamber) -> size_t{
  for (auto line : sprite) {
    chamber.at(sprite_height_pos++) |= line;
  }
  return sprite_height_pos;
}

auto solve(std::string_view input) -> int64_t {
  auto const sprites = std::array<Sprite, 5>{
    Sprite(
      {uint8_t{0b00111100}}),
    Sprite(
      {uint8_t{0b00010000},
       uint8_t{0b00111000},
       uint8_t{0b00010000}}),
    Sprite(
      {uint8_t{0b00111000},
       uint8_t{0b00001000},
       uint8_t{0b00001000}}),
    Sprite(
      {uint8_t{0b00100000},
       uint8_t{0b00100000},
       uint8_t{0b00100000},
       uint8_t{0b00100000}}),
    Sprite(
      {uint8_t{0b00110000},
       uint8_t{0b00110000}})
  };
  
  auto constexpr max_iter = size_t{2022};
  auto constexpr max_chamber_height = size_t{max_iter * 4 + 3};
  auto chamber = Chamber{};
  chamber.resize(max_chamber_height, 0);
  auto current_height = size_t{};
  auto gas_dir_index = size_t{};
  
  for (auto iter = size_t{}; iter<max_iter; ++iter) {
    auto sprite = sprites.at(iter % sprites.size());
    auto sprite_height_pos = current_height + 3U;
    while (true) {
      auto const backup_sprite = sprite;
      if (shift(input.at((gas_dir_index++)%input.size()), sprite)) {
        if (collision(sprite, sprite_height_pos, chamber)) {
          sprite = backup_sprite;
        }
      }
      if (sprite_height_pos == 0 || collision(sprite, sprite_height_pos-1, chamber)) {
        current_height = std::max(current_height, draw(sprite, sprite_height_pos, chamber));
        break;
      } 
      --sprite_height_pos;
    }
  }

  // for (auto pos = size_t{}; pos < current_height; ++pos) {
  //   fmt::print("{:0>8b}\n", chamber.at(pos));
  // }
  
  return int64_t(current_height);
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
