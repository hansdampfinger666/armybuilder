#pragma once

#include <optional>

#include <generic/types.h>
#include <generic/serialize.h>

struct Units
{
    const vector<string> UnitFields
    {
        "ID",
        "Text ID"
    };

    enum UnitsViewFilter : uint32
    {
        None        = 0,
        NotInitial  = 1
    };


    struct Unit
    {
        uint32 id_;
        uint32 txt_id_;
    };

    vector<uint32> id_;
    vector<uint32> txt_id_;

    uint32              add(const string& txt);
    uint32              add(const uint32 id, const string& txt);
    bool                del(const uint32 id, Units& trashbin);
    std::optional<Unit> get(const uint32 id);

    CEREAL_LD_SV(id_, txt_id_);
};
