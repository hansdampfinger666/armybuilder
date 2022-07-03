#include "text.h"

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
  id_[index.value()] = 0;
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
Texts::get_ids(const vector<size_t>& indexes)
{
  return vec::get_values(id_, indexes);
}

vector<string>
Texts::get_txts(const vector<size_t>& indexes)
{
  return vec::get_values(txt_, indexes);
}

vector<string>
Texts::get_txts(const vector<i32>& ids)
{
  vector<string> txts;
  txts.resize(ids.size());

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

vector<size_t>
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
