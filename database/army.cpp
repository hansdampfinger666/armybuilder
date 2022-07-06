#include "army.h"

Armies::Armies(Texts* texts)
  : texts_(texts)
{}

i32
Armies::add(const string& name)
{
  auto txt_id_db = texts_->add(name);
  auto entry_index = vec::index(txt_id_, txt_id_db);

  if (entry_index)
    return id_[entry_index.value()];
  else
    return append({ 0, txt_id_db });
}

i32
Armies::append(const Army& army)
{
  curr_id_++;
  id_.push_back(curr_id_);
  txt_id_.push_back(army.txt_id_);
  frag_ = vec::calc_frag(id_);
  return curr_id_;
}

bool
Armies::del(const i32 id, Armies& trashbin)
{
  auto index = vec::index(id_, id);
  if (!index)
    return false;

  trashbin.append({ id_[index.value()], txt_id_[index.value()] });
  id_[index.value()] = 0;
  frag_ = vec::calc_frag(id_);
  return true;
}

std::optional<Armies::Army>
Armies::get(const i32 id)
{
  auto index = vec::index(id_, id);
  if (!index)
    return {};

  return Army{ id_[index.value()], txt_id_[index.value()] };
}

vector<string>
Armies::get_names(const vector<i32>& ids)
{
  vector<i32> txt_ids(ids.size(), 0);

  for (i32 i = 0; auto id : ids) {
    auto index = vec::index(id_, id);
    if (!index)
      continue;
    txt_ids[i] = txt_id_[index.value()];
    i++;
  }
  return texts_->get_txts(txt_ids);
}

vector<string>
Armies::get_names()
{
  return texts_->get_txts(txt_id_);
}

string
Armies::get_name(const i32 id)
{
  auto result = vec::vkkv(id, id_, txt_id_, texts_->id_, texts_->txt_);
  if (result)
    return result.value();
  else
    return "";
}
