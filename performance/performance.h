#pragma once

#include <generic/print.h>
#include <generic/serialize.h>
#include <generic/types.h>
#include <generic/vec_ops.h>

#include <chrono>

namespace performance {

static const string benchmark_filepath = std::filesystem::current_path() /=
  "BENCHMARK";

struct Benchmark
{
  string name_;
  vector<string> clock_names_;
  vector<string> clock_dates_;
  vector<u64> ns_times_;

  Benchmark(const string& name);
  ~Benchmark();
  void save_clock(const struct Clock* clock);
  void print();

  CEREAL_LD_SV(name_, clock_names_, ns_times_);
};

struct Clock
{
  Benchmark* benchmark_ = nullptr;
  string name_ = {};
  string data_ = {};
  std::chrono::steady_clock::time_point begin_ = {}, end_ = {};

  Clock(Benchmark* benchmark, const string& clock_name);
  Clock(const string& clock_name);
  ~Clock();
};

inline Benchmark* benchmark = new Benchmark("Armybuilder2000");

static constexpr float ns_us_ = 0.001f;
static constexpr float ns_ms_ = 0.000001f;
static constexpr float ns_s_ = 0.000000001f;
}
