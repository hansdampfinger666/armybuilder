#pragma once

#include <optional>

#include <database/text.h>
#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>

struct Armies
{
    const vector<string> ArmyFields
    {
        "ID",
        "Text"
    };

    enum ArmiesViewFilter : uint32
    {
        None = 0,
        NotInitial = 1
    };

    struct Army
    {
        uint32 id_;
        uint32 txt_id_;
    };

    vector<uint32> id_;
    vector<uint32> txt_id_;

    uint32 curr_id_ = 0;
    f32 defrag_ = 0.f;

    Texts* texts_;

    explicit Armies(Texts* texts);
    std::optional<uint32> add(const string& str);
    std::optional<uint32> add(const uint32 id, const string& txt);
    bool                  del(const uint32 id, Armies& trashbin);
    std::optional<Army>   get(const uint32 id);
    vector<uint32>        get_ids(const vector<size_t>& indexes);
    vector<string>        get_names(const vector<size_t>& indexes);
    vector<size_t>        get_indexes(const ArmiesViewFilter filter);

    CEREAL_LD_SV(id_, txt_id_, curr_id_, defrag_);
};
