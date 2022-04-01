#include "text.h"

std::optional<uint32> Texts::add(const string& txt)
{
    auto idx_opt = index(txt_, txt);

    if(!idx_opt)
    {
        curr_id_++;
        id_.emplace_back(curr_id_);
        txt_.emplace_back(txt);
        defrag_ = calc_frag(id_);
        return curr_id_;
    }
    return idx_opt;
}

std::optional<uint32> Texts::add(const uint32 id, const string& txt)
{
    auto idx_opt = index(id_, id);

    if(idx_opt)
    {
        auto idx = idx_opt.value();
        txt_[idx] = txt;
        return idx;
    }
    return add(txt);
}

bool Texts::del(const uint32 id, Texts& trashbin)
{
    auto idx_opt = index(id_, id);

    if(idx_opt && lng_ == trashbin.lng_)
    {
        auto idx = idx_opt.value();
        trashbin.id_.emplace_back(id_[idx]);
        trashbin.txt_.emplace_back(txt_[idx]);
        id_[idx] = 0;
        defrag_ = calc_frag(id_);
        return true;
    }
    return false;
}

std::optional<Text> Texts::get(const uint32 id)
{
    auto idx_opt = index(id_, id);

    if(idx_opt)
    {
        auto idx = idx_opt.value();
        return Text{ id_[idx],
                     txt_[idx],
                     lng_ };
    }
    return std::optional<Text>{};
}

vector<uint32> Texts::get_ids(const vector<size_t>& indexes)
{
    return get_values(id_, indexes);
}

vector<string> Texts::get_txts(const vector<size_t>& indexes)
{
    return get_values(txt_, indexes);
}

vector<size_t> Texts::get_indexes(const TextsViewFilter filter)
{
    switch(filter)
    {
    case TextsViewFilter::None:
        return index_all(id_);
        break;
    case TextsViewFilter::NotInitial:
        return index_where_not_initial(id_);
        break;
    default:
        break;
    }
}





