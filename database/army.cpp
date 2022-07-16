#include "army.h"

u64
Armies::add(const string& name)
{
  auto txt_id_db = texts_->add(name);
  auto entry_index = vec::index(txt_id_, txt_id_db);

  if (entry_index)
    return id_[entry_index.value()];
  else
    return append({ 0, txt_id_db });
}

u64
Armies::append(const Army& army)
{
  curr_id_++;
  id_.push_back(curr_id_);
  txt_id_.push_back(army.txt_id_);
  frag_ = vec::calc_frag(id_);
  return curr_id_;
}

bool
Armies::del(const u64 id, Armies& trashbin)
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
Armies::get(const u64 id)
{
  auto index = vec::index(id_, id);
  if (!index)
    return {};
  return Army{ id_[index.value()], txt_id_[index.value()] };
}

  opt<Armies::ArmyReadable> 
  Armies::get_readable(const u64 id)
{
	auto index = vec::index(id_, id);	
	if(!index)
		return {};
	ArmyReadable army_read;
	army_read.id_ = id_[index.value()];
	army_read.txt_ = get_name(index.value()).value(); 
	return army_read;
}
