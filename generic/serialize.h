#pragma once

#include <cereal/access.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <filesystem>
#include <fstream>
#include <generic/types.h>
#include <iostream>

#define CEREAL_LD_SV(...)                                                      \
  template<class Archive>                                                      \
  void save(Archive& ar) const                                                 \
  {                                                                            \
    ar(__VA_ARGS__);                                                           \
  };                                                                           \
                                                                               \
  template<class Archive>                                                      \
  void load(Archive& ar)                                                       \
  {                                                                            \
    ar(__VA_ARGS__);                                                           \
  };

auto
export_data(auto& object, const string& full_path)
{
  std::ofstream ofs(full_path);

  if (ofs.is_open()) {
    cereal::BinaryOutputArchive oarchive(ofs);
    oarchive(object);
    ofs.close();
  }
}

auto
import_data(auto& object, const string& full_path)
{
  if (!std::filesystem::exists(full_path)) {
    return;
  }
  std::ifstream ifs(full_path);

  if (ifs.is_open()) {
    cereal::BinaryInputArchive iarchive(ifs);
    iarchive(object);
    ifs.close();
  }
}
