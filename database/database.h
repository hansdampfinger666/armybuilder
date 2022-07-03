#pragma once

#include <database/army.h>
#include <database/model.h>
#include <database/text.h>
#include <database/unit.h>
#include <generic/serialize.h>

#include <iostream>

enum DBTypes : i32
{
  NONE = 0,
  TEXTS = 1,
  ARMIES = 2,
  UNITS = 3,
  MODELS = 4
};

class Db
{
public:
  Texts* texts_;
  Armies* armies_;
  Units* units_;
  Models* models_;

  const vector<string> db_txt_{
    "Texts",
    "Armies",
    "Units",
    "Models",
  };

  Db();
  ~Db();
  void create_test_data();

private:
  void create_text_db(Texts& texts);
  void create_army_db(Armies& armies);
  void create_unit_db(Units& units);
  void create_model_db(Models& models);
};

static const string text_db_path = std::filesystem::current_path() /= "TEXTS";
static const string army_db_path = std::filesystem::current_path() /=
  "ARMY";
static const string unit_db_path = std::filesystem::current_path() /=
  "UNITS";
static const string model_db_path = std::filesystem::current_path() /=
  "MODELS";
