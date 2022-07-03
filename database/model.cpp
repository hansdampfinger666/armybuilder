#include "model.h"

Models::Models(Texts* texts)
  : texts_(texts)
{}

i32
Models::add(const string& name)
{
  auto txt_id_db = texts_->add(name);
  auto entry_index = vec::index(txt_id_, txt_id_db);

  if (entry_index)
    return id_[entry_index.value()];
  else
    return append({ 0, 0, 0, txt_id_db });
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

  trashbin.append({ army_id_[index.value()],
                    unit_id_[index.value()],
                    id_[index.value()],
                    txt_id_[index.value()] });
  id_[index.value()] = 0;
  frag_ = vec::calc_frag(id_);
  return true;
}

std::optional<Models::Model>
Models::get(const i32 id)
{
  auto index = vec::index(id_, id);
  if (!index)
    return {};

  return Model{ army_id_[index.value()],
                unit_id_[index.value()],
                id_[index.value()],
                txt_id_[index.value()] };
}

vector<string> 
Models::get_names(const vector<i32>& ids)
{
	vector<i32> txt_ids(ids.size(), 0);

	for (i32 i = 0; auto id : ids) {
		auto index = vec::index(id_, id);
		if(!index)
			continue;
		txt_ids[i] = txt_id_[index.value()];
		i++;
	}
	return texts_->get_txts(txt_ids);
}
