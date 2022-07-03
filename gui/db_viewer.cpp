#include "db_viewer.h"
#include "generic/qt_table.h"

DatabaseViewer::DatabaseViewer(QWidget* parent, const DB* db)
  : db_(db)
  , table_view_(new QTableView())
  , table_model_(new QStandardItemModel)
  , layout_(new QGridLayout(this))
  , okay_canc_buttons_(
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel))
{
  for (i32 i = 1; const aut& btn_txt : db_->db_txt_) {
    buttons_.push_back(new QPushButton{ QString::fromStdString(btn_txt) });
    QObject::connect(buttons_[i - 1], &QPushButton::pressed, this, [this, i] {
      const DBTypes type{ i };
      switch_tables(type);
    });
    layout_->addWidget(buttons_[i - 1], 0, i);
    i++;
  }
  layout_->addWidget(table_view_, 1, 0, 1, db_->db_txt_.size() + 1);
  layout_->addWidget(okay_canc_buttons_, 2, db_->db_txt_.size() - 1, 1, 2);
  table_view_->setModel(table_model_);
}

void
DatabaseViewer::switch_tables(const DBTypes db_type)
{
  if (active_view_ == db_type)
    return;

  table_model_->clear();
  active_view_ = db_type;

  switch (db_type) {
    case NONE:
      break;
    case TEXTS:
      create_table_model(table_model_,
                         db_->texts_->TextFields,
                         db_->texts_->id_,
                         db_->texts_->txt_);
      break;
    case ARMIES:
      create_table_model(table_model_,
                         db_->armies_->ArmyFields,
                         db_->armies_->id_,
                         db_->texts_->get_txts(db_->armies_->txt_id_));
      break;
    case UNITS:
      create_table_model(table_model_,
                         db_->units_->UnitFields,
                         db_->units_->id_,
                         db_->texts_->get_txts(db_->units_->txt_id_));
      break;
    case MODELS:
      create_table_model(table_model_,
                         db_->models_->ModelFields,
                         db_->models_->army_id_,
                         db_->models_->unit_id_,
                         db_->models_->id_,
                         db_->texts_->get_txts(db_->models_->txt_id_));
      break;
    default:
      break;
  }
  table_view_->resizeColumnsToContents();
}

DatabaseViewer::~DatabaseViewer()
{
  delete table_view_;
  delete table_model_;
  delete layout_;
  delete okay_canc_buttons_;

  for (auto btn : buttons_) {
    delete btn;
  }
}
