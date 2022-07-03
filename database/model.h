#pragma once

#include <optional>

#include <database/text.h>
#include <generic/serialize.h>
#include <generic/types.h>
#include <generic/vec_ops.h>

class Models
{
public:
  const vector<string> field_names_{
    "Army",
    "Unit",
    "ID",
    "Name",
  };
  static const i32 id_table_position_ = 2;

  enum ModelsViewFilter : i32
  {
    None = 0,
    NotInitial = 1
  };

  struct Model
  {
    i32 army_id_ = 0;
    i32 unit_id_ = 0;
    i32 id_ = 0;
    i32 txt_id_ = 0;
  };

  vector<i32> army_id_;
  vector<i32> unit_id_;
  vector<i32> id_;
  vector<i32> txt_id_;

  i32 curr_id_ = 0;
  f32 frag_ = 0.f;

  Texts* texts_;

  Models(Texts* texts);
  i32 add(const string& name);
  i32 add(const string& name, const i32 unit_id);
  i32 add(const string& name, const i32 unit_id, const i32 army_id);
  i32 append(const Model& model);
  bool del(const i32 id, Models& trashbin);
  std::optional<Model> get(const i32 id);
  vector<string> get_names(const vector<i32>& ids);

  CEREAL_LD_SV(army_id_, unit_id_, id_, txt_id_, curr_id_, frag_);
};
