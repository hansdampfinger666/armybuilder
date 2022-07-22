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
    i32 army_id_ = 0;
    i32 unit_id_ = 0;
  };

  struct ModelReadable : public AbstractDatabase::AbstractEntryReadable
  {
    string army_txt_ = { "" };
    string unit_txt_ = { "" };
  };

  vector<i32> army_id_;
  vector<i32> unit_id_;

  Models(const vector<string>& field_names, i32 id_field_position)
    : AbstractDatabase::AbstractDatabase(field_names, id_field_position){};
  i32 add(const string& name);
  i32 add(const string& name, const i32 unit_id);
  i32 add(const string& name, const i32 unit_id, const i32 army_id);
  opt<ModelReadable> get_readable(const i32 id);
  i32 append(const Model& model);
  bool del(const i32 id, Models& trashbin);
  opt<Model> get(const i32 id);

  CEREAL_LD_SV(army_id_, unit_id_, id_, txt_id_, curr_id_, frag_);
};
