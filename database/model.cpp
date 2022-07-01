#include "model.h"

Models::Models(Texts* texts):
    texts_(texts)
{}

i32 Models::add(const string& name)
{
    auto idx_txt_db = index(texts_->txt_, name);

    if(idx_txt_db)  // text was found in text database
    {
        auto txt_id = texts_->id_[idx_txt_db.value()];

        if(index(txt_id_, txt_id))
        {
            return {};
        }
        else
        {
            // texts exists, but model with the same name does not exist
            army_id_.push_back(0);
            unit_id_.push_back(0);
            id_.push_back(++curr_id_);
            txt_id_.push_back(txt_id);
            frag_ = calc_frag(id_);
            return curr_id_;
        }
    }
    else    // text was not found in text databse
    {
        army_id_.push_back(0);
        unit_id_.push_back(0);
        id_.push_back(++curr_id_);
        txt_id_.push_back(texts_->add(name));
        frag_ = calc_frag(id_);
        return curr_id_;
    }
}

bool Models::del(const i32 id, Models& trashbin)
{
    auto idx_opt = index(id_, id);

    if(idx_opt)
    {
        auto idx = idx_opt.value();
        trashbin.army_id_.emplace_back(army_id_[idx]);
        trashbin.unit_id_.emplace_back(unit_id_[idx]);
        trashbin.id_.emplace_back(id_[idx]);
        trashbin.txt_id_.emplace_back(txt_id_[idx]);
        return true;
    }
    return {};
}

std::optional<Models::Model> Models::get(const i32 id)
{
    auto idx_opt = index(id_, id);

    if(idx_opt)
    {
        auto idx = idx_opt.value();
        return Model{
            army_id_[idx],
            unit_id_[idx],
            id_[idx],
            txt_id_[idx]
        };
    }
    return {};
}

