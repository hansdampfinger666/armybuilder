#pragma once

#include "generic/types.h"
#include <generic/serialize.h>
#include <generic/vec_ops.h>
#include <database/database.h>

static const string text_db_path = std::filesystem::current_path() /= "TXT.dat";
static const string army_db_path = std::filesystem::current_path() /=
  "ARMY.dat";
static const string unit_db_path = std::filesystem::current_path() /=
  "UNITS.dat";
static const string model_db_path = std::filesystem::current_path() /=
  "MODELS.dat";

class TestData
{
public: 
  db* db_;

  TestData(db* db)
    : db_(db)
  {
    create_text_db(*db_->texts_);
    create_army_db(*db_->armies_);
    create_unit_db(*db_->units_);
    create_model_db(*db_->models_);
  }

  ~TestData()
  {
    export_data(*(db_->texts_), text_db_path);
    export_data(*(db_->armies_), army_db_path);
    export_data(*(db_->units_), unit_db_path);
    export_data(*(db_->models_), model_db_path);
  }

  void create_text_db(Texts& texts);
  void create_army_db(Armies& armies);
  void create_unit_db(Units& units);
  void create_model_db(Models& models);
};

void
TestData::create_text_db(Texts& texts)
{
  import_data(*db_->texts_, text_db_path);

  for (int i = 0; i < 10; i++) {
    string str = string("Text") + std::to_string(i) + string("_") +
                 std::to_string(texts.lng_);
    texts.add(str);
  }
}

void
TestData::create_army_db(Armies& armies)
{
  import_data(*db_->armies_, army_db_path);

  for (int i = 0; i < 10; i++) {
    string str = string("Army") + std::to_string(i);
    armies.add(str);
  }
}

void
TestData::create_unit_db(Units& units)
{
  import_data(*db_->units_, unit_db_path);

  for (int i = 0; i < 10; i++) {
    string str = string("Unit") + std::to_string(i);
    units.add(str);
  }
}

void
TestData::create_model_db(Models& models)
{
  import_data(*db_->models_, model_db_path);

  for (int i = 0; i < 10; i++) {
    string str = string("Model") + std::to_string(i);
    models.add(str);
  }
}
