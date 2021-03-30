#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "zip.hpp"
#include "range.hpp"
#include <vector>

TEST_CASE("Basic zip", "[zip]") {
  std::vector v1{1,2,3,4};
  std::vector v2{2.3, 4.1, 2.2, 0.1};

  for (auto [x, y] : Zip(v1, v2))
    REQUIRE(v2[x-1] == y);
}

TEST_CASE("Zip of ranges of unequal length", "[zip]") {
  std::vector v1{1,2,3};
  auto r = Range(4, 10);

  int z=0;
  for (auto [x, y] : Zip(v1, r))
    z += x+y;

  REQUIRE(z == 1+2+3+4+5+6);
}


TEST_CASE("Constant ranges", "[zip]") {
  const std::vector v1{1,2,3};
  const std::vector v2{4,5,6};

  int z=0;
  for (auto [x, y] : Zip(v1, v2))
    z += x+y;

  REQUIRE(z == 1+2+3+4+5+6);
}


TEST_CASE("Const reference to zipped types", "[zip]") {
  const std::vector v1{1,2,3};
  const std::vector v2{4,5,6};

  int z=0;
  for (const auto& [x, y] : Zip(v1, v2))
    z += x+y;

  REQUIRE(z == 1+2+3+4+5+6);
}

TEST_CASE("Non-const reference to zipped types", "[zip]") {
  std::vector v1{1,2,3};
  std::vector v2{4,5,6};

  for (auto& [x, y] : Zip(v1, v2))
    x += y;

  REQUIRE(v1 == std::vector{5, 7, 9});
}
