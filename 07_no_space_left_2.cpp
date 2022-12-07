#include "puzzle_input/07.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/inlined_vector.h>
#include <cppcoro/generator.hpp>
#include <ctre.hpp>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/lower_bound.hpp>
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/all.hpp>
#include <range/v3/view/filter.hpp>
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

auto solve(std::string_view input) -> int64_t {
  auto current_dir_size = std::vector<int64_t>{};
  current_dir_size.reserve(1024);  // NOLINT
  auto dir_sizes = std::vector<int64_t>{};
  dir_sizes.reserve(1024);  // NOLINT

  for (auto [match, cd_dir, ls_size, ls_file] :
       ctre::range<R"_(\$ cd (\S+)|(\d+) (\S+))_">(input)) {
    if (cd_dir) {
      if (cd_dir.to_view() != "..") {
        current_dir_size.push_back(0);
      } else {
        dir_sizes.push_back(current_dir_size.back());
        current_dir_size.pop_back();
        current_dir_size.back() += dir_sizes.back();
      }
    } else if (ls_size) {
      current_dir_size.back() += ls_size.to_number<int64_t>();
    }
  }

  while (!current_dir_size.empty()) {
    dir_sizes.push_back(current_dir_size.back());
    current_dir_size.pop_back();
    if (!current_dir_size.empty()) {
      current_dir_size.back() += dir_sizes.back();
    }
  }

  static constexpr auto disk_space = int64_t{70'000'000};
  static constexpr auto free_space_required = int64_t{30'000'000};
  auto const used_space = dir_sizes.back();
  auto const reclaim_space = used_space - (disk_space-free_space_required);
  assert(reclaim_space > 0);
  ranges::sort(dir_sizes);
  auto dir_size_it = ranges::lower_bound(dir_sizes, reclaim_space);
  return *dir_size_it;
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
