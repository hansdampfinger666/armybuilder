#pragma once

#include <optional>

#include <database/abstract_database.h>

class Units : public AbstractDatabase
{
public:
  enum UnitsViewFilter : i32
  {
    None = 0,
    NotInitial = 1
  };

  struct Unit : public AbstractDatabase::AbstractEntry
  {
    u64 army_id_ = 0;
  };

  vector<u64> army_id_;

  Units(const vector<string>& field_names, u32 id_field_position)
    : AbstractDatabase::AbstractDatabase(field_names, id_field_position){};
  u64 add(const string& name);
  u64 add(const string& name, const u64 army_id);
  bool del(const u64 id, Units& trashbin);
  std::optional<Unit> get(const u64 id);
  vector<u64> get_ids_by_army(const u64 army_id);
  u64 append(const Unit& unit);

  CEREAL_LD_SV(army_id_, id_, txt_id_, curr_id_, frag_);
};
