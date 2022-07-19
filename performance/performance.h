#pragma once

#include <chrono>

#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>

class Performance
{
public: 
  struct Clock
  {
	string name_;
	f64 start, end;

	Clock(const Performance* performance);
	~Clock();
  };

  struct Benchmark
  {
	vector<string> name_;
	vector<Clock> clocks;

	Benchmark(const Performance* performance, const string& benchmark_name);
	~Benchmark();
  };

  vector<Benchmark> benchmarks_;
  vector<Clock> clocks_;

  void start_benchmark(const string& benchmark_name);
  void end_benchmark(const string& benchmark_name);
  void start_clock(const string& clock_name);
  void end_clock(const string& clock);

private:
  void load_from_disk();
  void save_to_disk();
};
