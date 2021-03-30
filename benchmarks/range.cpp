#include <benchmark/benchmark.h>
#include "range.hpp"
#include <cmath>

static void BM_IntegerRange(benchmark::State& state) {
  for (auto _ : state) {
    std::uint64_t sum = 0;
    for (auto i : Range(std::uint64_t(1'000'000)))
      benchmark::DoNotOptimize(sum += i);
  }
}
BENCHMARK(BM_IntegerRange);


static void BM_IntegerHandroll(benchmark::State& state) {
  for (auto _ : state) {
    std::uint64_t sum = 0;
    for (std::uint64_t i=0; i<1'000'000; i++)
      benchmark::DoNotOptimize(sum += i);
  }
}
BENCHMARK(BM_IntegerHandroll);


double f(double x) {
  return x*sin(x+1.2);
}

static void BM_RangeIntegral(benchmark::State& state) {
  for (auto _ : state) {
    double sum = 0.0;
    for (auto r = Range(0.0, 1.0, 1'000'000); auto x : r)
      benchmark::DoNotOptimize(sum += f(x)*step_size(0.0, 1.0, 1'000'000));
  }
}
BENCHMARK(BM_RangeIntegral);

static void BM_HandrollIntegral(benchmark::State& state) {
  for (auto _ : state) {
    double sum = 0.0;
    double low = 0.0, high = 1.0;
    int N = 1'000'000;
    double dx = (high-low)/N;
    for (int i = 0; i<N; i++)
      benchmark::DoNotOptimize(sum += f(low+i*dx)*dx);
  }
}
BENCHMARK(BM_HandrollIntegral);

BENCHMARK_MAIN();
