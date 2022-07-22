#pragma once

#include <optional>

#include <database/abstract_database.h>

class Armies : public AbstractDatabase
{
public:
  enum ArmiesViewFilter : i32
  {
    None = 0,
    NotInitial = 1
  };

  struct Army : public AbstractDatabase::AbstractEntry
  {};

  struct ArmyReadable : public AbstractDatabase ::AbstractEntryReadable
  {};

  Armies(const vector<string>& field_names, i32 id_field_position)
    : AbstractDatabase::AbstractDatabase(field_names, id_field_position){};
  i32 add(const string& str);
  i32 add(const i32 id, const string& txt);
  opt<ArmyReadable> get_readable(const i32 id);
  i32 append(const Army& army);
  bool del(const i32 id, Armies& trashbin);
  opt<Army> get(const i32 id);
  vector<size_t> get_indexes(const ArmiesViewFilter filter);

  CEREAL_LD_SV(id_, txt_id_, curr_id_, frag_);
};
