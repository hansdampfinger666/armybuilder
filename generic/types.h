#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>

//using int8      = int8_t;       // signed char -127 to 127
//using int16     = int16_t;      // short int -32,768 to 32,767
using int32     = int32_t;      // int -2,147,483,648 to 2,147,483,647
using int64     = int64_t ;     // long int -2,147,483,648 to 2,147,483,647

//using uint8     = uint8_t;      // unsigned char 0 to 255
//using uint16    = uint16_t;     // unsigned short int 0 to 65,535
using uint32    = int32_t;      // unsigned int 0 to 4,294,967,295
using uint64    = uint64_t ;    // unsigned long int 0 to 18,446,744,073,709,551,615

using f32       = float ;       // float
using f64       = double;       // double

using string       = std::string;
using string_view  = std::string_view;
template <typename T> using vector = std::vector<T>;
template <typename T, size_t N> using array = std::array<T, N>;
