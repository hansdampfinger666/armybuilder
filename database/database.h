#pragma once

#include <database/text.h>
#include <database/army.h>
#include <database/unit.h>
#include <database/model.h>

enum DBTypes : i32
{
  NONE = 0,
  TEXTS = 1,
  ARMIES = 2,
  UNITS = 3,
  MODELS = 4
};

class DB
{
public:
  class Texts* texts_;
  class Armies* armies_;
  class Units* units_;
  class Models* models_;

  const vector<string> db_txt_{
    "Texts",
    "Armies",
    "Units",
    "Models",
  };

  DB()
    : texts_(new class Texts)
    , armies_(new class Armies(texts_))
    , units_(new class Units(texts_))
    , models_(new class Models(texts_))
  {}

  ~DB()
  {
    delete texts_;
    delete armies_;
    delete units_;
    delete models_;
  }
};
