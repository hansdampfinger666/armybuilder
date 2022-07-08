#include "add_dataset.h"

AddDataset::AddDataset(QWidget* parent, const Db* db, const DBTypes active_view)
  : db_(db)
  , layout_(new QGridLayout(this))
{
  this->setWindowTitle("Add dataset");
  switch_view(active_view);
}

void
AddDataset::switch_view(const DBTypes new_view)
{
  if (new_view == active_view_)
    return;

  active_view_ = new_view;
  i32 column = 0;
  i32 row = 0;

  switch (active_view_) {
    case NONE:
      break;
    case TEXTS: {
      break;
    }
    case ARMIES: {
      for (const auto& label_txt : db_->armies_->field_names_) {
        layout_->addWidget(
          new QLabel(QString::fromStdString(label_txt), this), column, 0);
        column++;
      }
      row = db_->armies_->field_names_.size();
      break;
    }
    case UNITS: {
      for (const auto& label_txt : db_->units_->field_names_) {
        layout_->addWidget(
          new QLabel(QString::fromStdString(label_txt), this), column, 0);
        column++;
      }
      army_drop_down_= new QComboBox(this);
      for (const auto& army_name : db_->armies_->get_names()) {
        army_drop_down_->addItem(QString::fromStdString(army_name));
      }
      layout_->addWidget(army_drop_down_, 0, 1);
      QObject::connect(army_drop_down_,
                       &QComboBox::currentTextChanged,
                       this,
                       &AddDataset::army_drop_down_changed);
      row = db_->units_->field_names_.size();
      break;
    }
    case MODELS: {
      for (const auto& label_txt : db_->models_->field_names_) {
        layout_->addWidget(
          new QLabel(QString::fromStdString(label_txt), this), column, 0);
        column++;
      }
      army_drop_down_ = new QComboBox(this);
      unit_drop_down_ = new QComboBox(this);
      for (const auto& army_name : db_->armies_->get_names()) {
        army_drop_down_->addItem(QString::fromStdString(army_name));
      }
      for (const auto& unit_name : db_->units_->get_names()) {
        unit_drop_down_->addItem(QString::fromStdString(unit_name));
      }
      layout_->addWidget(army_drop_down_, 0, 1);
      layout_->addWidget(unit_drop_down_, 1, 1);
      row = db_->models_->field_names_.size();
      break;
    }
    default:
      break;
  }
  auto ok_canc_buttons =
    new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
  layout_->addWidget(ok_canc_buttons, column, 0, row - 1, 2);
  QObject::connect(
    ok_canc_buttons, &QDialogButtonBox::rejected, this, &AddDataset::close);
}

void
AddDataset::army_drop_down_changed(const QString& txt)
{
  auto str = txt.toStdString();
  if (army_drop_down_val_ == str)
    return;
  army_drop_down_val_ = str;
  auto army_txt_id = db_->texts_->get_id(str);
  std::optional<i32> army_id;
  if (army_txt_id)
    army_id = db_->armies_->get_id(str);
  else return;
  unit_drop_down_->clear();
  auto unit_txts = db_->units_->get_names(db_->units_->get_ids_by_army(army_id.value()));
  for(const auto& unit_txt : db_->units_->get_names(db_->units_->get_ids_by_army(army_id.value()))) {
	 unit_drop_down_->addItem(QString::fromStdString(unit_txt)); 
  }
}

AddDataset::~AddDataset()
{
  std::cout << "destructor of adddataset was called\n";
}
