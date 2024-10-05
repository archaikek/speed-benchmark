#pragma once
#include <chrono>
#include <random>
#define _RANDOM_UTILS

typedef std::chrono::steady_clock::time_point time_point;
typedef std::chrono::milliseconds ms;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;


typedef std::uniform_int_distribution<long long int> uid64;
typedef std::uniform_int_distribution<int> uid32;