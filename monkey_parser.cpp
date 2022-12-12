#include <ctre.hpp>

#include "monkey_parser.h"

auto parse_monkeys(std::string_view input) -> Monkeys {
  auto monkeys = std::vector<Monkey>{};
  monkeys.reserve(8U);  // NOLINT
  for (
      auto [match, starting_items, op, operand, div, true_branch, false_branch] : ctre::range<
          R"_(Starting items: ([0-9, ]+)\n  Operation: new = old ([+*]) (\d+|old)\n  Test: divisible by (\d+)\n    If true: throw to monkey (\d+)\n    If false: throw to monkey (\d+))_">(
          input)) {
    monkeys.emplace_back();
    for (auto [_, item] : ctre::range<R"_((\d+))_">(starting_items)) {
      monkeys.back().items.push_back(item.to_number<int64_t>());
    }
    if (*op.data() == '+') {
      if (operand.to_view() == "old") {
        monkeys.back().priority_update = [](auto v) { return v + v; };
      } else {
        monkeys.back().priority_update = [arg = operand.to_number<int64_t>()](auto v) {
          return v + arg;
        };
      }
    } else {
      assert(*op.data() == '*');
      if (operand.to_view() == "old") {
        monkeys.back().priority_update = [](auto v) { return v * v; };
      } else {
        monkeys.back().priority_update = [arg = operand.to_number<int64_t>()](auto v) {
          return v * arg;
        };
      }
    }
    monkeys.back().test_value = div.to_number<int64_t>();
    monkeys.back().target_if_true = true_branch.to_number<size_t>();
    monkeys.back().target_if_false = false_branch.to_number<size_t>();
  }
  return monkeys;
}
