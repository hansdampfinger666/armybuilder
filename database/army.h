#pragma once

#include <optional>

#include <database/text.h>
#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>

class Armies
{
public:
  const vector<string> ArmyFields{ "ID", "Text" };

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
  std::optional<i32> add(const string& str);
  std::optional<i32> add(const i32 id, const string& txt);
  bool del(const i32 id, Armies& trashbin);
  std::optional<Army> get(const i32 id);
  vector<i32> get_ids(const vector<size_t>& indexes);
  vector<string> get_names(const vector<size_t>& indexes);
  vector<size_t> get_indexes(const ArmiesViewFilter filter);

  CEREAL_LD_SV(id_, txt_id_, curr_id_, frag_);
};
