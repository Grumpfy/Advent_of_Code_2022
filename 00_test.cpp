#include <fmt/core.h>
#include <cppcoro/generator.hpp>
#include <absl/container/flat_hash_map.h>

auto fibonacci() -> cppcoro::generator<const int> {
  int fib_k_0 = 0;
  int fib_k_1 = 1;
  while (true) {
    co_yield fib_k_1;
    fib_k_0 = std::exchange(fib_k_1, fib_k_0 + fib_k_1);
  }
}

auto main() -> int {
  fmt::print("Hello, world!\n");
  for (auto fib : fibonacci()) {
    constexpr auto upper_bound = 10;
    if (fib > upper_bound) {break;}
    fmt::print("Fib: {}\n", fib);
  }
  auto absl_map = absl::flat_hash_map<int, int>{};
  absl_map[3] = 2;
  fmt::print("absl_map[{}]: {}\n", 3, absl_map[3]);
  return 0;
}
