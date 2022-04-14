#pragma once

#include <optional>

#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>

struct Texts
{
    enum Lng : uint32
    {
        EN = 0,
        DE = 1
    };

    const vector<string> TextFields
    {
        "ID",
        "Text ID"
    };

    enum TextsViewFilter : uint32
    {
        None       = 0,
        NotInitial = 1
    };

    struct Text
    {
         uint32 id_ = 0;
         string txt_ = {};
         Lng lng_ = EN;
    };

    vector<uint32> id_;
    vector<string> txt_;

    Lng lng_ = EN;
    uint32 curr_id_ = 0;
    f32 defrag_ = 0.f;

    uint32                  add(const string& txt);
    uint32                  add(const uint32 id, const string& txt);
    bool                    del(const uint32 id, Texts& trashbin);
    std::optional<Text>     get(const uint32 id);
    vector<uint32>          get_ids(const vector<size_t>& indexes);
    vector<string>          get_txts(const vector<size_t>& indexes);
    vector<size_t>          get_indexes(const TextsViewFilter filter);

    CEREAL_LD_SV(id_, txt_, lng_, curr_id_, defrag_);
};
