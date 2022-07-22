#pragma once

#include <disk_io/serialize.h>
#include <tools/types.h>
#include <tools/vec_ops.h>
//#include <boost/te.hpp>

class Texts;

class AbstractDatabase
{
public:
  struct AbstractEntry
  {
    i32 id_ = 0;
    i32 txt_id_ = 0;
  };

  struct AbstractEntryReadable
  {
    i32 id_ = 0;
    string txt_ = "";
  };

  vector<string> field_names_;
  i32 id_field_position_;

  vector<i32> id_;
  vector<i32> txt_id_;
  Texts* texts_ = nullptr;

  i32 curr_id_ = 0;
  f32 frag_ = 0.f;

  AbstractDatabase(const vector<string>& field_names, i32 id_field_position)
    : field_names_(field_names)
    , id_field_position_(id_field_position){};
  i32 add(const string& name);
  opt<string> get_name(const i32 id);
  vector<string> get_names();
  vector<string> get_names(const vector<i32>& ids);
  vector<string> get_names_by_idx(const vector<i32>& indexes);
  opt<i32> get_id(const string& name);
  vector<i32> get_ids(const vector<i32>& indexes);
};

class Texts
{
public:
  const vector<string> field_names_ = { "ID", "Text" };
  static const i32 texts_id_field_position_ = 0;

  enum Lng : i32
  {
    EN = 0,
    DE = 1
  };

  enum TextsViewFilter : i32
  {
    NONE = 0,
    NOT_INITIAL = 1
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
  f32 frag_ = 0.f;

  i32 add(const string& txt);
  i32 add(const i32 id, const string& txt);
  bool del(const i32 id, Texts& trashbin);
  opt<Text> get(const i32 id);
  opt<string> get_name(const i32 id);
  opt<i32> get_id(const string& txt);
  vector<i32> get_ids(const vector<i32>& indexes);
  vector<string> get_names(const vector<i32>& ids);
  vector<string> get_names_by_index(const vector<i32>& indexes);
  vector<i32> get_indexes(const TextsViewFilter filter);

  CEREAL_LD_SV(id_, txt_, lng_, curr_id_, frag_);
};

