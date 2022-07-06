#pragma once

#include <optional>

#include <database/text.h>
#include <generic/serialize.h>
#include <generic/types.h>
#include <generic/vec_ops.h>

class Armies
{
public:
  const vector<string> field_names_{ "ID", "Text" };
  static const i32 id_table_position_ = 0;

  enum ArmiesViewFilter : i32
  {
    None = 0,
    NotInitial = 1
  };

  struct Army
  {
    i32 id_;
    i32 txt_id_;
  };

  vector<i32> id_;
  vector<i32> txt_id_;

  i32 curr_id_ = 0;
  f32 frag_ = 0.f;

  Texts* texts_;

  explicit Armies(Texts* texts);
  i32 add(const string& str);
  i32 add(const i32 id, const string& txt);
  i32 append(const Army& army);
  bool del(const i32 id, Armies& trashbin);
  std::optional<Army> get(const i32 id);
  vector<i32> get_ids(const vector<size_t>& indexes);
  vector<string> get_names(const vector<i32>& ids);
  vector<size_t> get_indexes(const ArmiesViewFilter filter);
	vector<string> get_names();
	string get_name(const i32 id);

  CEREAL_LD_SV(id_, txt_id_, curr_id_, frag_);
};
