#pragma once

#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>
#include <database/text.h>

struct Army
{
    uint16 id_;
    uint32 txt_;
};

struct Armies
{
    vector<uint16> id_;
    vector<uint32> txt_;

    uint32 curr_id_ = 0;
    f32 defrag_ = 0.f;

    std::optional<uint32> add(const string& str);
    std::optional<uint32> add(const uint32 id, const string& txt);
    bool                  del(const uint32 id, Armies& trashbin);

    CEREAL_LD_SV(id_, txt_, curr_id_, defrag_);
};
