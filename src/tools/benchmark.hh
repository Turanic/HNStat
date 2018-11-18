#pragma once

#include <chrono>
#include <memory>
#include <unordered_map>

#ifndef NDEBUG
#define BENCH_START(name, bench)                                               \
  auto name = tools::Benchmark::benchmark_get().start_bench(bench);
#define BENCH_STOP(name)                                                       \
  if (name != nullptr)                                                         \
  {                                                                            \
    name.reset();                                                              \
  }
#else
#define BENCH_START(name, bench)                                               \
  (void)name;                                                                  \
  (void)bench;
#define BENCH_STOP(name) (void)name;
#endif

namespace tools
{
  class Benchmark
  {
  public:
    static auto& benchmark_get()
    {
      static Benchmark instance{};
      return instance;
    }

    void enable();

    struct Timer;
    struct Stat;
    std::unique_ptr<Timer> start_bench(const std::string& name);

  private:
    std::unordered_map<std::string, std::unique_ptr<Stat>> benchs_{};

    bool enabled_ = false;

    Benchmark() = default;
    ~Benchmark();
  };

  struct Benchmark::Stat
  {
    std::chrono::microseconds dur{0};
    unsigned int nb_run = 0;
  };

  class Benchmark::Timer
  {
  public:
    Timer(Stat* ptr)
        : start{std::chrono::system_clock::now()}
        , stats{ptr}
    {
    }

    ~Timer()
    {
      stats->dur += std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::system_clock::now() - start);
      stats->nb_run++;
    }

  private:
    std::chrono::system_clock::time_point start;
    Stat* stats;
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
  };
} // namespace tools