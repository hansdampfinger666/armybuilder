#pragma once

#include <database/army.h>
#include <database/model.h>
#include <database/unit.h>

static const string text_db_path = std::filesystem::current_path() /= "TEXTS";
static const string army_db_path = std::filesystem::current_path() /= "ARMY";
static const string unit_db_path = std::filesystem::current_path() /= "UNITS";
static const string model_db_path = std::filesystem::current_path() /= "MODELS";

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
  const vector<string> db_txt_{
    "Texts",
    "Armies",
    "Units",
    "Models",
  };

  const vector<string> armies_field_names_{ "ID", "Name" };
  const vector<string> units_field_names_{ "Army", "ID", "Name" };
  const vector<string> models_field_names_{
    "Army",
    "Unit",
    "ID",
    "Name",
  };
  const i32 texts_id_field_pos_ = 0;
  const i32 armies_id_field_pos_ = 0;
  const i32 units_id_field_pos_ = 1;
  const i32 models_id_field_pos_ = 2;

  Texts* texts_ = nullptr;
  Armies* armies_ = nullptr;
  Units* units_ = nullptr;
  Models* models_ = nullptr;

  Db();
  ~Db();
  void create_test_data();

private:
  void create_text_db(Texts& texts);
  void create_army_db(Armies& armies);
  void create_unit_db(Units& units);
  void create_model_db(Models& models);
};
