#include "database.h"

Db::Db()
  : texts_(new Texts)
  , armies_(new Armies(armies_field_names_, armies_id_field_pos_))
  , units_(new Units(units_field_names_, units_id_field_pos_))
  , models_(new Models(models_field_names_, models_id_field_pos_))
{
  armies_->texts_ = texts_;
  units_->texts_ = texts_;
  models_->texts_ = texts_;
}

void
Db::create_test_data()
{
  create_text_db(*texts_);
  create_army_db(*armies_);
  create_unit_db(*units_);
  create_model_db(*models_);
}

void
Db::create_text_db(Texts& texts)
{
  import_data(texts, text_db_path);

  for (int i = 0; i < 10; i++) {
    string str = string("Text") + std::to_string(i) + string("_") +
                 std::to_string(texts.lng_);
    texts.add(str);
  }
}

void
Db::create_army_db(Armies& armies)
{
  import_data(armies, army_db_path);

  for (int i = 0; i < 10; i++) {
    string str = string("Army") + std::to_string(i);
    armies.add(str);
  }
}

void
Db::create_unit_db(Units& units)
{
  import_data(units, unit_db_path);

  for (int i = 0; i < 10; i++) {
    string str = string("Unit") + std::to_string(i);
    units.add(str, i + 1);
  }
}

void
Db::create_model_db(Models& models)
{
  import_data(models, model_db_path);

  for (int i = 0; i < 10; i++) {
    string str = string("Model") + std::to_string(i);
    models.add(str, i + 1, i + 1);
  }
}

Db::~Db()
{
  export_data(*texts_, text_db_path);
  export_data(*armies_, army_db_path);
  export_data(*units_, unit_db_path);
  export_data(*models_, model_db_path);
  delete texts_;
  delete armies_;
  delete units_;
  delete models_;
}
