#pragma once

#include <array>
#include <generic/types.h>
#include <generic/serialize.h>


static const string txt_db_path = std::filesystem::current_path() /= "TXT_TEST.dat";

struct Texts_Test
{
    vector<u32> id;
    // 256 bit, 4 x 64 bit L1 cache line per string
    vector<std::array<char, 32>> txt;

    CEREAL_LD_SV(id, txt);
};

