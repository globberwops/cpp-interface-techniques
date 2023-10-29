// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <benchmark/benchmark.h>

#include "optional_map/map.hpp"

static void BM_MapCreation(benchmark::State& state) {
  for (auto _ : state) {
    gw::cpp_interface_techniques::optional_map::Map map;
  }
}

BENCHMARK(BM_MapCreation);  // NOLINT

BENCHMARK_MAIN();  // NOLINT
