#pragma once
#include <ranges>
#include <concepts>


template<typename It1, typename It2>
class ZipIterator {
  private:
    It1 it1;
    It2 it2;

  public:
    constexpr ZipIterator(It1 iter1, It2 iter2)
      : it1(iter1), it2(iter2) {}

    // Dereference
    auto operator*() const {
      return std::pair{*it1, *it2};
    }

    // Comparison
    template<typename It3, typename It4>
    auto operator==(const ZipIterator<It3, It4>& o) {
      return it1 == o.it1 || it2 == o.it2;
    }

    // Increment/decrement
    ZipIterator<It1, It2>& operator++() {
      ++it1;
      ++it2;
      return *this;
    }
    ZipIterator<It1, It2> operator++(int) {
      auto val = *this;
      this->operator++();
      return val;
    }
    ZipIterator<It1, It2>& operator--() {
      --it1;
      --it2;
      return *this;
    }
    ZipIterator<It1, It2> operator--(int) {
      auto val = *this;
      this->operator--();
      return val;
    }
};


template<std::ranges::range R1, std::ranges::range R2>
class Zip {
  private:
    std::ranges::iterator_t<R1> begin1;
    std::ranges::iterator_t<R2> begin2;
    std::ranges::sentinel_t<R1> end1;
    std::ranges::sentinel_t<R2> end2;

  public:
    constexpr Zip(R1& range1, R2& range2)
      : begin1(std::ranges::begin(range1)),
        begin2(std::ranges::begin(range2)),
        end1(std::ranges::end(range1)),
        end2(std::ranges::end(range2)) {}

    auto begin() const {
      return ZipIterator(begin1, begin2);
    }

    auto end() const {
      return ZipIterator(end1, end2);
    }
};


