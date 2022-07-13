#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

using i32 = int32_t; // int -2,147,483,648 to 2,147,483,647
using i64 = int64_t; // long int -2,147,483,648 to 2,147,483,647

using u32 = uint32_t; // unsigned int 0 to 4,294,967,295
using u64 = uint64_t; // unsigned long int 0 to 18,446,744,073,709,551,615

using f32 = float;  // float
using f64 = double; // double

using string = std::string;

template<typename T>
using vector = std::vector<T>;
template<typename T, size_t N>
using array = std::array<T, N>;
template<typename T>
using uptr = std::unique_ptr<T>;
