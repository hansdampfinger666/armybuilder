#include "unit.h"

i32
Units::add(const string& name)
{
  auto txt_id_db = texts_->add(name);
  auto entry_index = vec::index(txt_id_, txt_id_db);

  if (entry_index)
    return id_[entry_index.value()];
  else {
    Unit new_unit;
    new_unit.txt_id_ = txt_id_db;
    return append(new_unit);
  }
}

i32
Units::add(const string& name, const i32 army_id)
{
  auto id = add(name);
  auto index = vec::index(id_, id);

  if (index)
    army_id_[index.value()] = army_id;
  return id;
}

i32
Units::append(const Unit& unit)
{
  curr_id_++;
  army_id_.push_back(unit.army_id_);
  id_.push_back(curr_id_);
  txt_id_.push_back(unit.txt_id_);
  frag_ = vec::calc_frag(id_);
  return curr_id_;
}

bool
Units::del(const i32 id, Units& trashbin)
{
  auto index = vec::index(id_, id);
  if (!index)
    return false;
  auto trashed_unit = get(id);
  trashbin.append(trashed_unit.value());
  vec::erase_at_index(index.value(), id_, txt_id_, army_id_);
  frag_ = vec::calc_frag(id_);
  return true;
}

std::optional<Units::Unit>
Units::get(const i32 id)
{
  auto index = vec::index(id_, id);
  if (!index)
    return {};
  auto fetched_unit = Unit{ { id_[index.value()], txt_id_[index.value()] },
	  army_id_[index.value()] };
  return fetched_unit;
}

  opt<Units::UnitReadable> 
  Units::get_readable(const i32 id)
{
	auto index = vec::index(id_, id);	
	if(!index)
		return {};
	UnitReadable unit_read;
	unit_read.id_ = id_[index.value()];
	unit_read.txt_ = get_name(id).value(); 
	unit_read.army_txt_ = texts_->get_name(army_id_[index.value()]).value();
	return unit_read;
}
  
vector<i32>
Units::get_ids_by_army(const i32 army_id)
{
  return vec::get_values(id_, vec::indexes(army_id_, army_id));
}
