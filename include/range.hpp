#pragma once
#include <concepts>
#include <compare>
#include <cassert>

// Integer range

template<std::integral Int>
class RangeIterator;

template<std::integral Int, bool bound_check=false>
class Range {
  private:
    Int low, high;

  public:
    constexpr explicit Range(Int hi) : Range(0, hi) {}
    constexpr explicit Range(Int lo, Int hi) : low(lo), high(hi) {
      if constexpr (bound_check) {
        assert(hi >= lo);
      }
    }

    constexpr auto begin() const {
      return RangeIterator(low);
    }

    constexpr auto end() const {
      return RangeIterator(high);
    }

};


template<std::integral Int>
class RangeIterator {
  private:
    Int x;

  public:
    constexpr explicit RangeIterator(Int val) : x(val) {}

    // Comparison
    constexpr auto operator<=>(const RangeIterator&) const = default;

    // Deref
    constexpr auto operator*() const {
      return x;
    }

    // Increment/decrement
    constexpr RangeIterator& operator++() {
      ++x;
      return *this;
    }
    constexpr RangeIterator operator++(int) {
      auto val = *this;
      this->operator++();
      return val;
    }
    constexpr RangeIterator& operator--() {
      --x;
      return *this;
    }
    constexpr RangeIterator operator--(int) {
      auto val = *this;
      this->operator--();
      return val;
    }

    // Addition/subtraction
    constexpr RangeIterator& operator+=(Int inc) {
      x += inc;
      return *this;
    }
    constexpr RangeIterator operator+(Int inc) {
      return RangeIterator(x + inc);
    }
    constexpr RangeIterator& operator-=(Int inc) {
      x -= inc;
      return *this;
    }
    constexpr RangeIterator operator-(Int inc) {
      return RangeIterator(x - inc);
    }
};


// Floating point range
template<std::floating_point Float>
class FloatRangeIterator;

template<std::floating_point Float>
class FloatRange {
  private:
    Float low, high, dx;
    int nsteps;

  public:
    constexpr explicit FloatRange(Float lo, Float hi, int steps)
      : low(lo), high(hi), dx((hi-lo)/steps), nsteps(steps) {}

    constexpr auto begin() const {
      return FloatRangeIterator(low, dx, 0);
    }

    constexpr auto end() const {
      return FloatRangeIterator(low, dx, nsteps);
    }

    constexpr auto step_size() const { return dx; }

};


template<std::floating_point Float>
class FloatRangeIterator {
  private:
    Float low, dx;
    int index;

  public:
    constexpr FloatRangeIterator(Float lo, Float inc, int ix_init)
      : low(lo), dx(inc), index(ix_init) {}

    // Comparison
    constexpr auto operator<=>(const FloatRangeIterator&) const = default;

    // Deref
    constexpr auto operator*() const {
      return low + index*dx;
    }

    // Increment/decrement
    constexpr FloatRangeIterator& operator++() {
      ++index;
      return *this;
    }
    constexpr FloatRangeIterator operator++(int) {
      auto val = *this;
      this->operator++();
      return val;
    }
    constexpr FloatRangeIterator& operator--() {
      --index;
      return *this;
    }
    constexpr FloatRangeIterator operator--(int) {
      auto val = *this;
      this->operator--();
      return val;
    }
};


