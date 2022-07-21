#pragma once

#include <tools/types.h>

namespace conv {

template<typename T>
string
stringify(const T& input)
{
  return input;
}

template<typename T>
requires std::is_integral<T>::value || std::is_floating_point<T>::value string
stringify(const T& input)
{
  return std::to_string(input);
}

template<typename T>
vector<string>
stringify(const vector<T>& vec)
{
  vector<string> result;
  for (const auto& elem : vec)
    result.push_back(stringify(elem));
  return result;
}

}
