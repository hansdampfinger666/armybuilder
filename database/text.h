#pragma once

#include <optional>

#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>

class Texts
{
public:
  enum Lng : i32
  {
    EN = 0,
    DE = 1
  };

  const vector<string> TextFields{ "ID", "Text" };

  enum TextsViewFilter : i32
  {
    None = 0,
    NotInitial = 1
  };

  struct Text
  {
    i32 id_ = 0;
    string txt_ = {};
    Lng lng_ = EN;
  };

  vector<i32> id_;
  vector<string> txt_;

  Lng lng_ = EN;
  i32 curr_id_ = 0;
  f32 defrag_ = 0.f;

  i32 add(const string& txt);
  i32 add(const i32 id, const string& txt);
  bool del(const i32 id, Texts& trashbin);
  std::optional<Text> get(const i32 id);
  std::optional<i32> get_id(const string& txt);
  vector<i32> get_ids(const vector<size_t>& indexes);
  vector<string> get_txts(const vector<size_t>& indexes);
  vector<string> get_txts(const vector<i32>& ids);
  vector<size_t> get_indexes(const TextsViewFilter filter);

  CEREAL_LD_SV(id_, txt_, lng_, curr_id_, defrag_);
};
