#include "add_dataset.h"

AddDataset::AddDataset(QWidget* parent, const Db* db, const DBTypes active_view)
  : db_(db)
  , layout_(new QGridLayout(this))
{
  this->setWindowTitle("Add dataset");
  switch_view(active_view);
}

void
AddDataset::set_window_title(const DBTypes new_view)
{
  auto title =
    QString::fromStdString({ "Add dataset: " + db_->db_txt_[new_view - 1] });
  this->setWindowTitle(title);
}

void
AddDataset::switch_view(const DBTypes new_view)
{
  if (new_view == active_view_)
    return;

  active_view_ = new_view;
  set_window_title(active_view_);
  i32 row = 0;
  i32 column = 0;

  switch (active_view_) {
    case NONE:
      break;
    case TEXTS: {
      qt_generate::draw_label_column(
        this, layout_, db_->texts_->field_names_, row, column);
      row = 0;
      column++;
      auto id_display =
        qt_generate::draw_line_edit_column(this, layout_, row, column, 1);
      assert(id_display.size() == 1);
      id_display[0]->setReadOnly(true);
      id_display[0]->setText(QString::number(db_->texts_->curr_id_ + 1));
      data_edit_ =
        qt_generate::draw_line_edit_column(this, layout_, row, column, 1);
      break;
    }
    case ARMIES: {
      qt_generate::draw_label_column(
        this, layout_, db_->armies_->field_names_, row, column);
      row = 0;
      column++;
      auto id_display =
        qt_generate::draw_line_edit_column(this, layout_, row, column, 1);
      assert(id_display.size() == 1);
      id_display[0]->setReadOnly(true);
      id_display[0]->setText(QString::number(db_->armies_->curr_id_ + 1));
      data_edit_ =
        qt_generate::draw_line_edit_column(this, layout_, row, column, 1);
      break;
    }
    case UNITS: {
      qt_generate::draw_label_column(
        this, layout_, db_->units_->field_names_, row, column);
      army_drop_down_ = new QComboBox(this);
      army_drop_down_->addItems(qt_conv(db_->armies_->get_names()));
      layout_->addWidget(army_drop_down_, 0, 1);
      QObject::connect(army_drop_down_,
                       &QComboBox::currentTextChanged,
                       this,
                       &AddDataset::army_drop_down_changed);
      row = 1;
      column++;
      auto id_display =
        qt_generate::draw_line_edit_column(this, layout_, row, column, 1);
      assert(id_display.size() == 1);
      id_display[0]->setReadOnly(true);
      id_display[0]->setText(QString::number(db_->units_->curr_id_ + 1));
      data_edit_ =
        qt_generate::draw_line_edit_column(this, layout_, row, column, 1);
      break;
    }
    case MODELS: {
      qt_generate::draw_label_column(
        this, layout_, db_->models_->field_names_, row, column);
      army_drop_down_ = new QComboBox(this);
      unit_drop_down_ = new QComboBox(this);
      army_drop_down_->addItems(qt_conv(db_->armies_->get_names()));
      army_drop_down_changed(army_drop_down_->currentText());
      row = 0;
      column++;
      layout_->addWidget(army_drop_down_, row, column);
      row++;
      layout_->addWidget(unit_drop_down_, row, column);
      row++;
      QObject::connect(army_drop_down_,
                       &QComboBox::currentTextChanged,
                       this,
                       &AddDataset::army_drop_down_changed);
      auto id_display =
        qt_generate::draw_line_edit_column(this, layout_, row, column, 1);
      assert(id_display.size() == 1);
      id_display[0]->setReadOnly(true);
      id_display[0]->setText(QString::number(db_->models_->curr_id_ + 1));
      data_edit_ =
        qt_generate::draw_line_edit_column(this, layout_, row, column, 1);
      break;
    }
    default:
      break;
  }
  auto ok_canc_buttons =
    new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
  layout_->addWidget(ok_canc_buttons, row, 0, row - 1, 2);
  QObject::connect(
    ok_canc_buttons, &QDialogButtonBox::rejected, this, &AddDataset::close);
  QObject::connect(ok_canc_buttons,
                   &QDialogButtonBox::accepted,
                   this,
                   &AddDataset::commit_changes);
}

void
AddDataset::army_drop_down_changed(const QString& txt)
{
  auto str = txt.toStdString();
  if (army_drop_down_val_ == str)
    return;
  army_drop_down_val_ = str;

  auto army_id = db_->armies_->get_id(str);
  if (!army_id || !unit_drop_down_)
    return;
  unit_drop_down_->clear();
  auto unit_ids = db_->units_->get_ids_by_army(army_id.value());
  auto unit_txts = db_->units_->get_names(unit_ids);
  unit_drop_down_->addItems(qt_conv(unit_txts));
}

void
AddDataset::commit_changes()
{
  u64 added_id = 0;

  switch (active_view_) {
    case NONE:
      break;
    case TEXTS: {
      assert(data_edit_.size() == 1);
      added_id = db_->texts_->add(data_edit_[0]->text().toStdString());
      break;
    }
    case ARMIES: {
      assert(data_edit_.size() == 1);
      added_id = db_->armies_->add(data_edit_[0]->text().toStdString());
      break;
    }
    case UNITS: {
      assert(data_edit_.size() == 1);
      auto army_id = db_->armies_->get_id(army_drop_down_val_);
      added_id =
        db_->units_->add(data_edit_[0]->text().toStdString(), army_id.value());
      break;
    }
    case MODELS: {
      assert(data_edit_.size() == 1);
      auto army_id = db_->armies_->get_id(army_drop_down_val_);
      auto unit_id =
        db_->units_->get_id(unit_drop_down_->currentText().toStdString());
      added_id = db_->models_->add(
        data_edit_[0]->text().toStdString(), unit_id.value(), army_id.value());
      break;
    }
  }
  emit added_db_entry(added_id);
  this->close();
}

AddDataset::~AddDataset() {}
