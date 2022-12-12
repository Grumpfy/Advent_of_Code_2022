#include <cstdint>
#include <string_view>
#include <vector>

struct Monkey {
  std::vector<int64_t> items;
  std::function<int64_t(int64_t)> priority_update;
  int64_t test_value;
  size_t target_if_true;
  size_t target_if_false;
  int64_t inspected_items = 0;
};
using Monkeys = std::vector<Monkey>;

auto parse_monkeys(std::string_view input) -> Monkeys;
