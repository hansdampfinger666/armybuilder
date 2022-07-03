#include "unit.h"

Units::Units(Texts* texts)
  : texts_(texts)
{}

i32
Units::add(const string& name)
{
  auto txt_id = texts_->get_id(name);

  if (txt_id && exists(txt_id_, txt_id.value()))
    return {};

  army_id_.push_back(0);
  id_.push_back(++curr_id_);

  // TODO make this more concise somehow

  //    auto txt_id = texts_->get_id(name);

  //    if(txt_id)
  //    {
  //        if(exists(txt_id_, txt_id.value()))
  //        {
  //            // text exists and unit with the same name already exists
  //            return {};
  //        }
  //        else
  //        {
  //            // text exists, but unit with the same name does not exist
  //            army_id_.push_back(0
  //            id_.push_back(++curr_id_);
  //            txt_id_.push_back(txt_id.value());
  //            frag_ = calc_frag(id_);
  //            return curr_id_;
  //        }
  //    }
  //    else
  //    {
  //        // text was not found in database
  //        army_id_.push_back(0);
  //        id_.push_back(++curr_id_);
  //        txt_id_.push_back(texts_->add(name));
  //        frag_ = calc_frag(id_);
  //        return curr_id_;
  //    }
}

i32
Units::add(const i32 id, const string& name)
{}

bool
Units::del(const i32 id, Units& trashbin)
{}

std::optional<Units::Unit>
get(const i32 id)
{}
