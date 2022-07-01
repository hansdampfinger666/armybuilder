#pragma once

#include <database/text.h>
#include <database/army.h>
#include <database/unit.h>
#include <database/model.h>


class db
{
public: 
	  Texts* texts_;
  Armies* armies_;
  Units* units_;
  Models* models_;

//  enum db_txt {
//	0 = none;
//	1 = "Texts";
//	2 = "Armies";
//	3 = "Units";
//	4 = "Models";
//  }

  const vector<string> db_txt{
    "Texts",
    "Armies",
    "Units",
    "Models",
  };

	db() :
		texts_(new Texts)
		, armies_(new Armies(texts_))
		, units_(new Units(texts_))
		, models_(new Models(texts_))
	{}
};
