#include "model.h"

i32
Models::add(const string& name)
{
  auto txt_id_db = texts_->add(name);
  auto entry_index = vec::index(txt_id_, txt_id_db);

  if (entry_index)
    return id_[entry_index.value()];
  else {
    Model new_model;
    new_model.txt_id_ = txt_id_db;
    return append(new_model);
  }
}

i32
Models::add(const string& name, const i32 unit_id)
{
  auto id = add(name);
  auto index = vec::index(id_, id);

  if (index)
    unit_id_[index.value()] = unit_id;
  return id;
}

i32
Models::add(const string& name, const i32 unit_id, const i32 army_id)
{
  auto id = add(name, unit_id);
  auto index = vec::index(id_, id);

  if (index)
    army_id_[index.value()] = army_id;
  return id;
}

opt<Models::ModelReadable>
Models::get_readable(const i32 id)
{
  auto index = vec::index(id_, id);
  if (!index)
    return {};
  ModelReadable models_read;
  models_read.id_ = id_[index.value()];
  models_read.txt_ = get_name(id).value();
  models_read.army_txt_ = texts_->get_name(army_id_[index.value()]).value();
  models_read.unit_txt_ = texts_->get_name(unit_id_[index.value()]).value();
  return models_read;
}

i32
Models::append(const Model& model)
{
  curr_id_++;
  army_id_.push_back(model.army_id_);
  unit_id_.push_back(model.unit_id_);
  id_.push_back(curr_id_);
  txt_id_.push_back(model.txt_id_);
  frag_ = vec::calc_frag(id_);
  return curr_id_;
}

bool
Models::del(const i32 id, Models& trashbin)
{
  auto index = vec::index(id_, id);
  if (!index)
    return false;
  auto trashed_model = get(id);
  trashbin.append(trashed_model.value());
  vec::erase_at_index(index.value(), id_, txt_id_, army_id_, unit_id_);
  frag_ = vec::calc_frag(id_);
  return true;
}

std::optional<Models::Model>
Models::get(const i32 id)
{
  auto index = vec::index(id_, id);
  if (!index)
    return {};
  auto fetched_model = Model{ { id_[index.value()], txt_id_[index.value()] },
	  army_id_[index.value()], unit_id_[index.value()] };
  return fetched_model;
}
