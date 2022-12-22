#include <string_view>

static inline constexpr auto puzzle_input = std::string_view(
R"_(>>><<<>>>><<<<>><<<<>><>>><>>>><><<<<>>>><<>>><<<>><>>><<>><>>><<>>><<>><>>><>>><<<<><<<>><<<>>><<>>>><>>>><<<<>>>><<<>>>><<<>>>><<<>>>><<<<><<<<><<<>>>><<<>>><<<><<<>>>><<>><<<>><<<><<<><<>><<>>>><<>>><<><<>><<><<>>><<>>>><<<><>>><<<<>>><<<<><><<<><<>>><<>><>>>><<<<><<>>><<<>>><<<<>>>><<<<>><<<>>><<<<>>><<<>>>><<<>>>><<<>>>><<<<>>><<<>>>><<<><><<<><<<><>>>><>><>>><<><<<>>><><<<>><<<<>><<>><>><>>>><<<<>>><<>>>><<><<>><<<<>><><<>>>><<<>>>><<<>><<<<>>><<<<>>>><>>>><<>><<<><<<>><<<<>>><<<<>><<>><><<<<>>><<><<<>>>><<>>>><<<<>>>><<<>>>><<<>>><<>>>><>>>><<>>><<<>>>><>>>><<<<>>>><>>>><<<><<<>>>><>><>>><>>>><<<><>><<<<><<><>>>><<><<<<><<<>>><><>>>><<><>>>><<<>>><<<<>>><>>>><<<>>><<<<>>>><<>><<<>>><<>>>><<><<<<><><<<<>>><<<<>>><<<<>>><<>>><<<>><<>>><<<<>>>><<<<>>>><<<>>><>>>><<<<>>><>><<>>><<><<<<>><<>>><<<><><<<<>>>><<<>><><<>>><<>><<><>>><<<>>>><<<<>>><<<><<>><<>>><>><<>>>><<>>>><<>>>><<>>>><<>><>>>><<><>>>><<<>>>><<<>>><<><<<<><>><<<>><<<<>><<<<>><<>>>><<<>><<>><>>>><<<>>>><<<>>>><<<<>>><<<<>><<><<<>>>><<<>>>><<>>><<><><<<<>><<<<><<<><<>><<><<<<>><<<<>><<<<><<<<>>>><<<>><<<><<<<>>><>><>>><>>><<><<<<>>><<<<>>>><<<><<<>><<<>><<<>>><<>>><<<>>><>>><<><>>>><<<<>>><<<<>>>><<<>>>><>>><>><<>><<<>><><<<>>>><<<>>><><<><<><<<<><<<<>>><<<<><>>>><<<>>>><<>>><<<<>>>><<<<>>><<>>><>>>><>><<<>>><<<<>>>><>><<>>><<<><<<>>><<<<><<<<><>>>><<><>><<<<>><<<<>>>><>>>><<>>><<<<><<<><<>>>><<><<<>>><<<><<<<>><<>>><<<<>><>>>><><<<<>>><<<>>>><><<>>>><<<<>>>><<<<>><<<>>><<<<>>><<<>>><>>>><<>><>><<<<><<<>><<>>>><>><>>>><<<>>><<><<<>><<>><<<>><<>>><<<<>><><<<>>><<<<>>><<<>>><<<<>>><<<<>>><<>>><>>><<>>><<<>><>><<<>>><<<<>><>>>><<<>>><>><>><<<>>><>>><<>>><<>><<<<>>>><<>>>><<<<>><>>><<<<>>><<<<>>>><<<>>>><>><<<>>>><<<><<>>><<><>><<<>>><<<>>><<><>>><<>>>><<<><<<<><><>>><<<<>>>><<<<><<<>><<<>><<<>>><<<>>>><>>><<<>>><<<<>><<>><<<>>>><<<><<>>><<<>><<<<>>>><<<<>><<<><<<>>><<<<><>><<<><<<<>>>><<><>><<<>>><<>>>><>>>><<<><<<<>>>><<>>>><<>><<<>>>><><<<>><<>>><<><<<<>>><<>><<<>><<<<>>>><<>>><<>>><<<<>>>><<>>><<<>><<>>>><<>><<<>>><<<>>><<>>>><<<<><>><>>><<<<>>><<<><<>><<<><<<>>><>><<<><<><<<>>><<><<>>><>><<<>>>><<><>><<<>>><<<>>>><<>><><>>><<<<>>><<>><<<><<<<>>>><>>><<<<>>><><><<<<><><<>><<>><>>>><<<<>>><<<>>>><><<<<>><<<<>><<><<<<>>><>>><<<><<<>>><<<>>><<<<>>><<>><<<<><<<<>>>><<>><<<<>>><<<>><<>>><<<><<<>>>><<>><<<<>>><<<<>>>><<<>>>><<>>><>>><<<<><<<<><><<>>>><<<>><>>>><<<>>><>><>><><<>>><<<>>>><<<>><<><<><<>><<<<><<<><>>>><>>><>><>>><<<<>>><<<><>><<<<>>><<<<><><>>>><<>>>><<>>>><<>>>><<<<>>><>><<<<>>>><<<>><<><<<<>>>><>><<>><>><>>>><<>>><>>>><<<<>><<<>>><<<>>>><<<<>><<><<<<>><>>><<>>>><<<<>><<<<>><>>>><><<<<>>>><<><<<><<>><<<<>>>><<><<<<><<<<>>>><>><<>><<><<<<>><<<><<<<>>><><<>>><>>>><<<<>><>>><<<><<>>><>>>><>><<<>>>><>>><>><<<<>>><<<><<<<>>>><<<>>><<<>><<<>>>><<<>>><<<<>>><<<<><>>><<<<>>>><>><>>><>>><<>><<<>>>><<<>><<<>>><<<>>><<>>>><<<<><<<<><<<<>>>><<<>>><<<>>>><<<><<<<>>><<<<><<<<>><<<<>><>><<<<><<<<>>><<>><><<<<><><<<<>><<>>>><<>><>><<<<><<<<>>>><<>>>><<<>>><<<<>>>><<<<>>>><<<<>><<><>>>><>>>><<><<<<><<>><<>>>><<>><<<>>><>><><<<<><<><<>><<<>>><<>>><<>>>><<<><>>>><<<<>>>><<<>><<<><<<<><<><<<><<<>>>><<<<>>>><<<<><<<<><>>><><<<<>>>><<<<><<>><<<>>>><<<<>>><>><<<<>>><<<<>>>><<<<>>><>>><<>>><<<><>>><><<<<>>><>>><>><><<<>><>>>><><<<>><<><<<>>><<><<<<>>>><<<<>>>><<<<>><<<><<<><><>>><<<><>><<>>><>>>><<<<>>><<>>><<<<>>>><<<<>>><<<>><<<<><>><<<<>>><>><<<>>><<<<>><<<<>><<>>><<<<>>>><<<>>><<>>>><<>>>><<><<<<><<>>><<<<>><<>><<<><<<<>><<<>>><<<>>>><<<<>><>>>><>><<>>>><><<>><<<<><><<<>>><<<>><<<>>>><<<<>>>><<<<>>>><<<>>>><>>>><<<>>>><>><<<>><>>><<<><>>><<><>>><<<<>><<<<>><<><<<>>>><<<<>>><<<<>>>><<<<><<<<>>><<<>>><<<>><<<>>><<<<>><<<><<<>><<<><<<<>>>><<<>>><<<><<<<>>><<<>>>><><<<<>>><><<<>>>><<<<>><>>>><<><>>>><><<<><<<<>>>><<<>><<>>><<<<><<>>><><<><<>>><<<>>><<<<><<>><<><<<>>><<>>>><<<>>><<><>>><<<>><<<>>><>>>><<<<>>>><<>>>><<>><<>><<<<><<<>>>><<<<>>>><><<<><<>><<<<>>><>><>><<>>>><<<><<<>>>><>>><<><<><<<<>>>><<<>>>><<>><><<<<>>><<>>><<<<>><>><<<<><<>>><<<>>><<<<>>><>><<<>><<>>>><<<>>><><<<>><<<<>><>>><<>><<<<>>><<><<>>><>>><><<<<>>>><<<<>><<>><<<>>><<<<>>><<>>>><<><<<<>>>><>>><<>>>><>>><<<<>>>><<<<>>><<>>><<<>>><<<><<<<><>>>><<>><><<<<>>>><>>>><<<<>><>>>><>><>>>><<<<>>>><<>>>><<><<<<>>>><<<><>>><<<<><<>>><<<><<<<><>><<<>>><<>><<<<><<<>>>><<>><<>>><<<><<<<>><><<<><>>><<<<>>>><<>>><>>>><>>><<<<>>><<<><><<>>>><<<>><<<<>>>><<><<<>>><<<<>><<<<>>><>>>><<<<>><<>>><<<<>>><>>><<<<><<<>>>><<>>><<<<><<><<<>>>><<<<>><><<<<>>>><<<>>>><<<<><<>><<>>><<<>>><>><><<>>><<>><<<<><>><<<><>>><<<<>>><<>>><>><<<>>>><<<<>><><<<>><<<>><<>><<<>><<<<>>>><<<<><<<<>>>><<<<>>><<<><<<>>><>>>><<<>>><<<<>>>><>>>><>>><<<<>>>><<>>><<>>>><<>><>>><<>>>><>>>><<<<>>>><>>><<<><<<<><>>><<<<><>>>><<<>>>><>>><<>><<><<<>><<<<><<<><<<>><<<><<>>>><<<><<>>>><<><>><<>>><<>>><>><<<>><>>>><<>>>><<>>><>>><<<<>>>><<><<>>>><<<>>>><><<>>>><<<<>><>><<><>><<><>>><>>>><<<>>>><><<<>>><<<>>>><<<>>><<<>>><>><>>><>>>><<<><<<>><>>><<><<>><<<<><<>><<>><<<>>><<>>><<<<>>><<><>>><<>>>><<<><<<>>><><<<<><<><<<>><<<<>>><><<<<><<<<><>>>><<>>>><<<<>>><<<<>><<<<>><<<><<>><<>><>><<<<>>><<<<><>><<<<><<<<><<><<>><<<><<>>><<<<>>><<<>>>><<<>><>><<<>>><<<>><>>><<>>>><<>>><<<<>><<>>>><<<<><>>><<<><<<>>><<<>>><<><>>><>>>><<<>><<<<>><><<<>>>><<<<>>><<>><<<<>>><<<>><><<>>>><<>>>><<<>>>><<<><<<>>>><<<<>><<<<>>>><<>>><<<<><>>>><>>>><>><>>>><<<>>>><>>><<<<><<<><<<<>>><><<<<>><>><<>>>><<<>><<<>>>><>><<<><>>><<<><>><<<<>><<>>>><<>><>>><<<<>>><<<>><>>><<<>>><<>>><>>><<<<>>>><<>>>><>>>><<<<>><<<>><><>><<><<<>>>><<<>>><<<>>>><<<<>><<<<><<<>>>><<>><>><<<<>>><<>>>><>>>><<<<>>><><<<>>>><<<>>><<<>>>><<<><<>><<>>>><<<<>><<<>>>><<<>><<<<>>>><<>><<>>><<>>><<>>>><<>><>>><><<>>>><>><>><>><>><<<>><<<<>><>>><<<><><<<<>>>><<<>>>><<<<>><<<<><>>><<><<<<>><<<<>><<<>>>><<<<>>><>>>><<<<>>><>><>>>><<<>>><<<<>><>>>><<><<<<>>>><<<>>>><<<><<<>>>><<<>>><<<>><>>><<<>>><<<<>>>><<<>><>>>><<>>><<>>><><<<<>>><<>><<>>><<>>><<<<>>><<<>><>>><<>>>><<<>><<<>>>><<<>><<<<>><<>>>><<<<><>>><<<><<<>>>><<>><<<<><<<>>><>>><<<<>>><<<<>><<<<>><<<<>><<<>><<<>>><<<<>>>><<<>>>><><>><>><<<>>><<<<><<<<>>><<<<><<<<><><>>><<<>>>><<<<>>>><>><<<<><<<>><>>>><<<>><>>>><<<>><>>><<>>><<<<>><><<>>><<<<><<<<><<<><<<<>>><<><<><>>>><<><<<<>><>>><<<<>>><>>><<<<><<<<>>><>>>><<>>>><<<>>>><<<>>>><>>><>><<<<><<<<>><<<<>>>><<<<>><>>><<>>><<<>>><>>><<<><><><>>><<<<><<>>>><>><<>><<<<>><<<<>>><><<<<>><<>>><<<>>>><>><><><<<><>><<<<>>><>>>><>>><<>><<<<><<>>><<<>>><<><<<>>><>>>><<<<>>>><<<><>>><>>><<<>><>>><<><<>><<><<<>><><>>><<<<>>>><<<>><<<><<<>>><<>><>>>><>>>><<<>>><<<>>><<>>>><<<<><<>>>><<>>>><<<<>>>><<<<>>>><<<>>><<>>><<>><<>>><<<<>><<<><>>>><<<>>><<<>>><<>>>><>><<>>>><<<<>>><<>>><<<<>><<>>>><<<<>>><>>>><<>>><<<>>><<<>><<<<><>>>><<><<>>><>>><<<>><<><<<<>>>><<<<>><>>>><<>>><<<>><<>>>><>><<>><<<<>><<>>><>>><<<>><<>><><<<<>>><>><<><>>>><<>>>><<<<>><><>>>><>>>><>>>><<>><<<<><>>>><<<>><<<>>><<>><<<><<<<>>><>>>><<>>><<<<>><>><<<<>><>>>><<<>><<<<>>>><<<<>>><>>>><<><<<><<>>><<><<>><<<><<><>>>><<>>><>><<<<>>>><<<<><>><<<>><>><<<><><<<<>>><<>>><<<>><<<><<<>>>><<<<>>><<<><>>>><<<><<><>><<<<>>>><<<<><<>>><<<<>>><<>>><>>>><<<>>>><<><>>><<<<>><>>><<<><<<>>>><<<<>><<<<>>><>>>><<>>><>>>><>>>><<>>>><<<>><<<><<<><<>>>><<<<><<>>><<>><>><<>><<<>>><<<<>>>><<>>><<<>><<>>><><>>>><<<>>><<<<>>>><<<<>>><<<<>><<><<<>><>><<<<><<<<>>><<<<><<<<><<<>>><<<<>>><<<<>>>><<<>>>><<<<>>><<<<><<<>>>><<><<<>>>><<<<>>>><>>>><<<<>>><<><<>><<>><<>>>><<<<><>>><<><<>><<><<<>><<>>>><<<<><>><<<><<<><<<>>>><<<<><<><<<<><<>>><>>>><<>>><<<>>>><<><<<<><<<<>><<<<><<><<>><<>>>><>><<<>>><<><<<>>>><<<>>>><<>><<><>><>><<<<>><<<>><>>>><<<<><<<>>>><<><<<<>><<<<><<<<>><<<<>>>><<<>>><<<<>>><<><<<>>>><>>>><<<>>>><<<<>><<><<<<>>><<<>>><<>><<<><><<>>>><<><<<>>>><<<>>>><<<<>>>><>>>><<<>>>><<<>>><>><<<><<<>>><<><<>>>><<<><<<>>><<>><<<>><><<<<>><><<<><<>>><<<>><<<<>>>><<>><<<<>>><<<<><>><>>>><<>><<<<>>>><<>><<<<>>>><>>>><<<>><<<>>>><><>>>><<>>><<>>><<<>><>><<><>><<<<>><<<<><<><<<<>><<<>>><<<><<<>>>><<<>>>><<<>>>><<<<>>>><<>>><<<<>><<<<>><<>>><>>><<><>><<<><><>>>><<><>>><<>>><<<>><>>><<><<<<>>><<>><<<<>>><<><>><<><<<<>>><<<>>>><>><<<<><<>>><<>><<<>>>><<<>><<<<>><<<<><<<>><>>><<<<>><<<<>>>><<<<><<>>><>>><<<<>>>><<<<>>><><><<<><<<<>>><><>><>>>><>>><>>>><<<>>>><<>><<<<><<<>>>><>>><<<<>>>><<>>>><<<<><<><<>>>><<>>><>><><>>><<<<>><>><<>>><<<>><>>><<>><<<><<>>>><<<<>>><<>>>><<<<>>><<><<<>>>><<<>>><<<>>><><<<>><<<<>>><>><<<<>><<>>><<<<><<<<>><<<<>>><>>><<>>><<>><<<>><>>><<<<>>><<<<><<<>>><<<>>>><<><><<<><<>><<>>>><<<>>>><<<<><<<<>>><>>>><<><<<<>><<<<>>>><<<<>>>><>>><<<<>><<<>>>><<<<>>><<<<>>>><<<<><>>>><<><>><<><<><<>>><<<<><<>>><<>>>><<<>><<<<><<<>>>><<<><>><<<<>>><<<>>><<<><<>><<<<>><<<><<>>>><><>>><<>>>><<>><>>>><<<><<>>>><<>>><<<<>><<<>>>><<>>>><<<<>>>><<<<>>><>><<<>>><<<<><<<>>>><<<>>>><>><<<<>>><<>><<<>>>><<>>><>>><<<<>><>>><<<>>><<<<><><<<>><<<<>>>><<<<>>>><<<<>>><>><><<>>>><<<>>>><<<>><<<>>><<>><<<<>><><<><<>>>><<>>><<<><<>>>><<<<>>>><<<>><>>><><<<><<<>>><<><<<<>>>><<<<>>><<>><<>>><<<<><<>>>><<>>>><<<>>>><<><>><<<>><<<<>>><<<<>>><<>><<<<>>>><<<<>>>><<<<><<<<>>>><<>>>><<<>>><<>><>>><<>>><<>>><<<>>>><<<>>><><>>>><<>><>>>><<<>><>>><<<><<>>><<><<<>><>>><<>><>>><<>>>><<<<>><<>>>><>><<<><<<<>>><<<><>>><<<<>>>><<<>><<<<><>>><<<<>><>>><<<>>>><<>>>><<<<>>><<><<<<>>><<<>>><><<<>>>><<><<<>>>><<>><>>>><<>>>><><<<><<>>>><<>><<>>><>><><<<>>>><<>>><<<<>><>>>><<<>><<><>>><<><<<>>>><<><<>>><>>>><<>>>><<<><<>>><>>><>><>><<<>>>><<<><<<>><<<<>><<<>><<>>>><>>>><<<<>>>><<>>><<><<<>>><<<<>><<<<>>>><<>><<<<><<><>>>><<<>>>><<>>><><<<<>><>>><<<<><<<<>>>><<<<>><>><>>>><<<<>>><<>>><>>>><<>>><<<<>>><><<<>>>><<>>><<<<>><<<><>>><><<><<><<><<<><<<>>>><<<>>>><<<<><>>>><>>><>><<>>><<<><>><<<<>>>><><<<>>><<<>><<><<<>>><<><<<>><<<><<<<>>><<>>>><<>>><<<><<<>><<><><<>>>><<>><<<>>>><<>>><<<<>>><<<<>>><<<>>>><<<<>><<<>>><<>>><<>>><>>><<>>><<>>><<<<>><<<<><<>><<<<>>>><>>><<>>>><<<<>><>><>>>><><>>>><>>>><<<>><<<<>>>><<<>>><<>>><<<<><<>><<<<>>><<<>>>><>>>><<<>><<<><<<>><<<<>><<><<>>><><<<<>><>><<>>><><<<<>>><<>>><<<><<>><<>><>><<>><<>>>><<<><<<<>>>><<<>>><<>><<<<>>><<<<>><><<<<>>>><<<<><>><>>>><<<><<>>>><<>>><<>><<<<>>>><><>><<<><>>>><<<>>><<<>>><>><<>>>><<<><<<><<<<><<>><<<>>><<<<>><<<<><<<<><<<>>>><<<><><<<<>><<><<>>>)_");
