#include "db_viewer.h"

DatabaseViewer::DatabaseViewer(QWidget* parent, const db* db)
  : db_(db)
  , table_view_(new QTableView())
  , layout_(new QGridLayout(this))
{
	// create buttons and add them to the widget
  for (int i = 0; const auto& btn_txt : db_->db_txt) {
    buttons_.push_back(new QPushButton{ QString::fromStdString(btn_txt) });
    layout_->addWidget(buttons_[i], 0, i);
    i++;
  }
  // add the table view area to the widget
  layout_->addWidget(table_view_, 1, 0, 1, db_->db_txt.size());

  // signals (probably can't be generic)
  for (const auto& btn : buttons_) {
	auto btn_name = btn->text().toStdString();
	if (btn_name == "Texts") {
		std::cout << "the text database was hit boi\n";
	} else if (btn_name == "Armies") {
		std::cout << "the armies database was hit boi\n";
	} else if (btn_name == "Units") {
		std::cout << "the units database was hit boi\n";
	} else if (btn_name == "Models") {
		std::cout << "the models databse was hit boi\n";
	}
  }
}

void
DatabaseViewer::switch_tables()
{
	std::cout << "this is a test if the button signals work\n"; 
	
	for (const auto& btn : buttons_) {
		std::cout << "button with the name of " << 
			btn->text().toStdString() << " was clicked\n";
	}
}

DatabaseViewer::~DatabaseViewer()
{
  delete table_view_;
  delete layout_;

  for (auto btn : buttons_) {
    delete btn;
  }
}
