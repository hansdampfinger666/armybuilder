#pragma once

#include <optional>

#include <database/abstract_database.h>

class AbstractDatabase;

class Armies : public AbstractDatabase
{
public:
  enum ArmiesViewFilter : i32
  {
    None = 0,
    NotInitial = 1
  };

  struct Army
  {
    u64 id_;
    u64 txt_id_;
  };

  Armies(const vector<string>& field_names, u32 id_field_position)
    : AbstractDatabase::AbstractDatabase(field_names, id_field_position){};
  u64 add(const string& str);
  u64 add(const u64 id, const string& txt);
  u64 append(const Army& army);
  bool del(const u64 id, Armies& trashbin);
  std::optional<Army> get(const u64 id);
  vector<size_t> get_indexes(const ArmiesViewFilter filter);

  CEREAL_LD_SV(id_, txt_id_, curr_id_, frag_);
};
