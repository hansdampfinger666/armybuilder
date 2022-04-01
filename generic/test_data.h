#pragma once

#include <generic/types.h>
#include <generic/serialize.h>
#include <generic/vec_ops.h>

#include <database/text.h>
#include <database/army.h>

static const string text_db_path = std::filesystem::current_path() /= "TXT.dat";
static const string army_db_path = std::filesystem::current_path() /= "ARMY.dat";

void create_text_db(Texts& texts);

struct TestData
{
    Texts texts_;
    Armies armies_;

    TestData()
    {
        create_text_db(texts_);
        create_army_db(armies_);
    }

    ~TestData()
    {
        export_data(texts_, text_db_path);
        export_data(armies_, army_db_path);
    }

    void create_text_db(Texts& texts);
    void create_army_db(Armies& armies);
};


void TestData::create_text_db(Texts& texts)
{
    import_data(texts, text_db_path);

    for(int i = 0; i < 10; i++)
    {
        string str = string("Text") + std::to_string(i)
                + string("_") + std::to_string(texts.lng_);
        texts.add(str);
    }
}


void TestData::create_army_db(Armies& armies)
{
    import_data(armies, army_db_path);
}
