#pragma once

#include <optional>

#include <database/abstract_database.h>

class Models : public AbstractDatabase
{
public:
  enum ModelsViewFilter : i32
  {
    None = 0,
    NotInitial = 1
  };

  struct Model : public AbstractDatabase::AbstractEntry
  {
    u64 army_id_ = 0;
    u64 unit_id_ = 0;
  };

  struct ModelReadable : public AbstractDatabase::AbstractEntryReadable
  {
    string army_txt_ = { "" };
    string unit_txt_ = { "" };
  };

  vector<u64> army_id_;
  vector<u64> unit_id_;

  Models(const vector<string>& field_names, u32 id_field_position)
    : AbstractDatabase::AbstractDatabase(field_names, id_field_position){};
  u64 add(const string& name);
  u64 add(const string& name, const u64 unit_id);
  u64 add(const string& name, const u64 unit_id, const u64 army_id);
  opt<ModelReadable> get_readable(const u64 id);
  u64 append(const Model& model);
  bool del(const u64 id, Models& trashbin);
  opt<Model> get(const u64 id);

  CEREAL_LD_SV(army_id_, unit_id_, id_, txt_id_, curr_id_, frag_);
};
