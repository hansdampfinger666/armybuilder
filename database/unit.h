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
    i32 army_id_ = 0;
  };

  struct UnitReadable : public AbstractDatabase::AbstractEntryReadable
  {
    string army_txt_ = { "" };
  };

  vector<i32> army_id_;

  Units(const vector<string>& field_names, i32 id_field_position)
    : AbstractDatabase::AbstractDatabase(field_names, id_field_position){};
  i32 add(const string& name);
  i32 add(const string& name, const i32 army_id);
  opt<UnitReadable> get_readable(const i32 id);
  bool del(const i32 id, Units& trashbin);
  std::optional<Unit> get(const i32 id);
  vector<i32> get_ids_by_army(const i32 army_id);
  i32 append(const Unit& unit);

  CEREAL_LD_SV(army_id_, id_, txt_id_, curr_id_, frag_);
};
