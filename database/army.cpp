#include "army.h"

Armies::Armies(Texts* texts)
  : texts_(texts)
{}

std::optional<i32>
Armies::add(const string& name)
{
  auto idx_txt_db = index(texts_->txt_, name);

  if (idx_txt_db) // text was found in text database
  {
    auto txt_id = texts_->id_[idx_txt_db.value()];

    if (index(txt_id_, txt_id)) {
      // text exists and army with the same name already exists
      return {};
    } else {
      // text exists, but army with the same name does not exist
      id_.push_back(++curr_id_);
      txt_id_.push_back(txt_id);
      frag_ = calc_frag(id_);
      return curr_id_;
    }
  } else {
    // text was not found in text databse
    id_.push_back(++curr_id_);
    txt_id_.push_back(texts_->add(name));
    frag_ = calc_frag(id_);
    return curr_id_;
  }
}

bool
Armies::del(const i32 id, Armies& trashbin)
{
  auto idx_opt = index(id_, id);

  if (idx_opt) {
    auto idx = idx_opt.value();
    trashbin.id_.emplace_back(id_[idx]);
    trashbin.txt_id_.emplace_back(txt_id_[idx]);
    id_[idx] = 0;
    frag_ = calc_frag(id_);
    return true;
  }
  return false;
}

std::optional<Armies::Army>
Armies::get(const i32 id)
{
  auto idx_opt = index(id_, id);

  if (idx_opt) {
    auto idx = idx_opt.value();
    return Army{ id_[idx], txt_id_[idx] };
  }
  return {};
}
