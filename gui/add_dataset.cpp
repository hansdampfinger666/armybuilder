#include "add_dataset.h"

AddDataset::AddDataset(QWidget* parent, const Db* db, const DBTypes active_view)
  : db_(db)
  , active_view_(active_view)
  , okay_canc_buttons_(
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel))
{
  this->setWindowTitle("Add dataset");
  switch_view(active_view);
  QObject::connect(
    okay_canc_buttons_, &QDialogButtonBox::rejected, this, &AddDataset::close);
}

void
AddDataset::switch_view(const DBTypes new_view)
{
  if (new_view == active_view_)
    return;

  delete layout_;
  layout_ = new QGridLayout(this);
  active_view_ = new_view;

  switch (active_view_) {
    case NONE:
      break;
    case TEXTS: {
    }
    case ARMIES: {
    }
    case UNITS: {
    }
    case MODELS: {
      for (i32 i = 0; const auto& label : db_->models_->field_names_) {
        labels_.push_back(new QLabel(QString::fromStdString(label)));
        layout_->addWidget(labels_[i], i, 0);
        i++;
      }
      army_drop_down_ = new QComboBox(this);
      for (const auto& army_name : db_->armies_->get_names()) {
        army_drop_down_->addItem(QString::fromStdString(army_name));
      }
      layout_->addWidget(army_drop_down_, 0, 1);
    }
    default:
      break;
  }
}

AddDataset::~AddDataset()
{
	delete layout_;
	for(auto label : labels_)
		delete label;
	delete army_drop_down_;
}
