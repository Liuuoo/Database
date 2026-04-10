#pragma once
#include <chrono>
#include <cstdint>
std::chrono::system_clock::time_point getCustomEpoch();
std::uint64_t getTimestampSec();
std::uint64_t getTimestampMs();
