#include "abstract_database.h"

std::optional<string>
AbstractDatabase::get_name(const i32 id)
{
  auto result = vec::vkkv(id, id_, txt_id_, texts_->id_, texts_->txt_);
  if (result)
    return result.value();
  else
    return "";
}

vector<string>
AbstractDatabase::get_names()
{
  return texts_->get_names(txt_id_);
}

vector<string>
AbstractDatabase::get_names(const vector<i32>& ids)
{
  vector<i32> txt_ids(ids.size(), 0);

  for (i32 i = 0; auto id : ids) {
    auto index = vec::index(id_, id);
    if (!index)
      continue;
    txt_ids[i] = txt_id_[index.value()];
    i++;
  }
  return texts_->get_names(txt_ids);
}

std::optional<i32>
AbstractDatabase::get_id(const string& name)
{
  return vec::vkkv(name, texts_->txt_, texts_->id_, txt_id_, id_);
}

i32
Texts::add(const string& txt)
{
  auto index = vec::index(txt_, txt);
  if (index)
    return id_[index.value()];

  curr_id_++;
  id_.emplace_back(curr_id_);
  txt_.emplace_back(txt);
  frag_ = vec::calc_frag(id_);
  return curr_id_;
}

i32
Texts::add(const i32 id, const string& txt)
{
  auto index = vec::index(id_, id);
  if (!index)
    return add(txt);

  txt_[index.value()] = txt;
  return id_[index.value()];
}

bool
Texts::del(const i32 id, Texts& trashbin)
{
  auto index = vec::index(id_, id);
  if (!index || lng_ != trashbin.lng_)
    return false;
  trashbin.id_.emplace_back(id_[index.value()]);
  trashbin.txt_.emplace_back(txt_[index.value()]);
  vec::erase_at_index(index.value(), id_, txt_);
  frag_ = vec::calc_frag(id_);
  return true;
}

std::optional<Texts::Text>
Texts::get(const i32 id)
{
  auto index = vec::index(id_, id);
  if (!index)
    return {};
  return Text{ id_[index.value()], txt_[index.value()], lng_ };
}

std::optional<i32>
Texts::get_id(const string& txt)
{
  auto index = vec::index(txt_, txt);
  if (!index)
    return {};

  return index.value();
}

vector<i32>
                                          Texts::get_ids(const vector<i32>& indexes)
{
  return vec::get_values(id_, indexes);
}

opt<string>
Texts::get_name(const i32 id)
{
  for (auto i : id_)
    if (id == i)
      return txt_[i];
  return {};
}

vector<string>
Texts::get_names_by_index(const vector<i32>& indexes)
{
  return vec::get_values(txt_, indexes);
}

vector<string>
Texts::get_names(const vector<i32>& ids)
{
  vector<string> txts(ids.size(), { "" });

  for (i32 i = 0; auto id : ids) {
    auto idx = vec::index(id_, id);
    if (idx)
      txts[i] = txt_[idx.value()];
    i++;
  }
  if (txts.size() == 0)
    return {};
  return txts;
}

vector<i32>
Texts::get_indexes(const TextsViewFilter filter)
{
  switch (filter) {
    case TextsViewFilter::NONE:
      return vec::index_all(id_);
      break;
    case TextsViewFilter::NOT_INITIAL:
      return vec::index_where_not_initial(id_);
      break;
    default:
      break;
  }
}
