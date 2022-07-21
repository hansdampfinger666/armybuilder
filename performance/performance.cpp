#include "performance.h"
#include <string>

performance::Benchmark::Benchmark(const string& name)
  : name_(name)
{
  import_data(*this, performance::benchmark_filepath);
}

void
performance::Benchmark::save_clock(const Clock* clock)
{
  if (clock->name_ == "" ||
      clock->begin_ == std::chrono::steady_clock::time_point::min() ||
      clock->end_ == std::chrono::steady_clock::time_point::min())
    return;
  clock_names_.push_back(clock->name_);
  clock_dates_.push_back(clock->date_);
  ns_times_.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(
                        clock->end_ - clock->begin_)
                        .count());
}

void
performance::Benchmark::print()
{
  vector<float> us, ms, s;
  for (const auto ns : ns_times_) {
    us.push_back(ns * ns_us_);
    ms.push_back(ns * ns_ms_);
    s.push_back(ns * ns_s_);
  }
  new PrintTable("Performance results",
                 { "Clock name", "Date", "ns", "us", "ms", "s" },
                 clock_names_,
                 clock_dates_,
                 ns_times_,
                 us,
                 ms,
                 s);
}

performance::Clock::Clock(Benchmark* benchmark, const string& clock_name)
  : benchmark_(benchmark)
  , name_(clock_name)
{
  init();
}

performance::Clock::Clock(const string& clock_name)
  : benchmark_(performance::benchmark)
  , name_(clock_name)
{
  init();
}

void
performance::Clock::init()
{
  auto time_t = std::time(0);
  auto today = std::localtime(&time_t);
  date_ = std::to_string(today->tm_mon + 1) + "/" +
          std::to_string(today->tm_mday) + "/" +
          std::to_string(today->tm_year + 1900);
  begin_ = std::chrono::steady_clock::now();
}

performance::Clock::~Clock()
{
  end_ = std::chrono::steady_clock::now();
  benchmark_->save_clock(this);
}
