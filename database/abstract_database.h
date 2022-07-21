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
    u64 id_ = 0;
    u64 txt_id_ = 0;
  };

  struct AbstractEntryReadable
  {
	  u64 id_ = 0;
	  string txt_ = "";
  };

  vector<string> field_names_;
  u32 id_field_position_;

  vector<u64> id_;
  vector<u64> txt_id_;
  Texts* texts_ = nullptr;

  u64 curr_id_ = 0;
  f32 frag_ = 0.f;

  AbstractDatabase(const vector<string>& field_names, u32 id_field_position)
    : field_names_(field_names)
    , id_field_position_(id_field_position){};
  u64 add(const string& name);
  opt<string> get_name(const u64 id);
  vector<string> get_names();
  vector<string> get_names(const vector<u64>& ids);
  vector<string> get_names_by_idx(const vector<size_t>& indexes);
  opt<u64> get_id(const string& name);
  vector<u64> get_ids(const vector<size_t>& indexes);
};

class Texts
{
public:
  const vector<string> field_names_ = { "ID", "Text" };
  static const u32 texts_id_field_position_ = 0;

  enum Lng : u32
  {
    EN = 0,
    DE = 1
  };

  enum TextsViewFilter : u32
  {
    NONE = 0,
    NOT_INITIAL = 1
  };

  struct Text
  {
    u64 id_ = 0;
    string txt_ = {};
    Lng lng_ = EN;
  };

  vector<u64> id_;
  vector<string> txt_;

  Lng lng_ = EN;
  u64 curr_id_ = 0;
  f32 frag_ = 0.f;

  u64 add(const string& txt);
  u64 add(const u64 id, const string& txt);
  bool del(const u64 id, Texts& trashbin);
  opt<Text> get(const u64 id);
  opt<string> get_name(const u64 id);
  opt<u64> get_id(const string& txt);
  vector<u64> get_ids(const vector<size_t>& indexes);
  vector<string> get_names(const vector<u64>& ids);
  vector<string> get_names_by_index(const vector<size_t>& indexes);
  vector<size_t> get_indexes(const TextsViewFilter filter);

  CEREAL_LD_SV(id_, txt_, lng_, curr_id_, frag_);
};
