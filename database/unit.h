#pragma once

#include <optional>

#include <database/text.h>
#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>

class Units
{
public:
  const vector<string> UnitFields{ "ID", "Name" };

  enum UnitsViewFilter : i32
  {
    None = 0,
    NotInitial = 1
  };

  struct Unit
  {
    i32 army_id_ = 0;
    i32 id_ = 0;
    i32 txt_id_ = 0;
  };

  vector<i32> army_id_;
  vector<i32> id_;
  vector<i32> txt_id_;

  i32 curr_id_ = 0;
  f32 frag_ = 0.f;

  Texts* texts_;

  Units(Texts* texts);
  i32 add(const string& name);
  i32 add(const i32 id, const string& name);
  bool del(const i32 id, Units& trashbin);
  std::optional<Unit> get(const i32 id);

  CEREAL_LD_SV(army_id_, id_, txt_id_);
};
