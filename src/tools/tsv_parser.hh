#pragma once

#include <chrono>
#include <fstream>
#include <string>
#include <tuple>

namespace tools
{
  class TSVParser
  {
  public:
    using timepoint_t = std::chrono::system_clock::time_point;

    TSVParser(const std::string& file,
              std::string_view minimum_timestamp,
              std::string_view maximum_timestamp);

    std::tuple<timepoint_t, std::string, bool> read_element();

  private:
    std::ifstream reader;
    timepoint_t min_ts_{};
    timepoint_t max_ts_{};
  };
} // namespace tools
