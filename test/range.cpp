#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "range.hpp"

TEST_CASE("Basic range", "[range]") {
  int sum1=0, sum2=0;

  for (auto i : Range(10))
    sum1 += i;

  for (int i=0; i<10; i++)
    sum2 += i;

  REQUIRE(sum1 == sum2);
}

TEST_CASE("Range with lower bound", "[range]") {
  int sum1=0, sum2=0;

  for (auto i : Range(5, 10))
    sum1 += i;

  for (int i=5; i<10; i++)
    sum2 += i;

  REQUIRE(sum1 == sum2);
}


TEST_CASE("Floating point range", "[range]") {
  double sum1=0.0, sum2=0.0;

  for (auto x : Range(-5.0, 5.0, 100))
    sum1 += x;

  auto low = -5.0;
  auto high = 5.0;
  auto dx = (high-low)/100;
  for (int i=0; i<100; i++)
    sum2 += low+i*dx;

  REQUIRE(sum1 == sum2);
}

TEST_CASE("Simple integral", "[range]") {
  double sum1=0.0, sum2=0.0;

  auto f = [](int x) { return x*x; };

  for (auto x : Range(-5.0, 5.0, 100))
    sum1 += f(x)*step_size(-5.0, 5.0, 100);

  auto low = -5.0;
  auto high = 5.0;
  auto dx = (high-low)/100;
  for (int i=0; i<100; i++)
    sum2 += f(low+i*dx)*dx;

  REQUIRE(sum1 == sum2);
}

constexpr auto test_range(int low, int high) {
  auto sum = 0;
  for (auto i : Range(low, high))
    sum += i;
  return sum;
}


TEST_CASE("Range in a constexpr context", "[range]") {
  constexpr auto sum1 = test_range(0, 11);
  constexpr auto sum2 = 55;
  static_assert(sum1 == sum2, "range fail");

  REQUIRE(sum1 == sum2);
}

