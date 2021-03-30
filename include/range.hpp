#pragma once
#include <concepts>
#include <compare>
#include <ranges>

// Integer range

template<std::integral Int>
constexpr auto Range(Int low, Int high) noexcept {
  return std::ranges::views::iota(low, high);
}

template<std::integral Int>
constexpr auto Range(Int high) noexcept {
  return std::ranges::views::iota(static_cast<Int>(0), high);
}

// Floating point range

template<std::floating_point Float, std::integral Int>
constexpr auto step_size(Float low, Float high, Int nsteps) noexcept {
  return (high-low)/nsteps;
}

template<std::floating_point Float, std::integral Int>
constexpr auto Range(Float low, Float high, Int nsteps) noexcept {
  return std::ranges::views::iota(0, nsteps)
    | std::ranges::views::transform(
        [low, dx=step_size(low, high, nsteps)](auto i) {
          return low + i*dx;
        });
}


