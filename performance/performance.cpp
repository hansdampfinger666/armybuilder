#include "performance.h"

void
Performance::start_benchmark(const string& benchmark_name)
{
	if(vec_ops::index(benchmarks_.name_, benchmark_name))
		return; 
	benchmarks_.push_back{ this, benchmark_name };
}

void
Performance::end_benchmark(const string& benchmark_name)
{
}

void
Performance::start_clock(const string& clock_name)
{
}

void
Performance::end_clock(const string& clock)
{
}

Performance::Clock::Clock() {}

Performance::~Clock::Clock() {}

Performance::Benchmark::Benchmark()
	: name_(benchmark_name)
{

}

Performance::~Benchmark::Benchmark() {}
