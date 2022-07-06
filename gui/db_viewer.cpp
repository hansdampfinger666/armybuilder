#include "db_viewer.h"

DatabaseViewer::DatabaseViewer(QWidget* parent, const Db* db)
  : db_(db)
  , table_view_(new QTableView())
  , table_model_(std::make_unique<QStandardItemModel>())
  , layout_(std::make_unique<QGridLayout>(this))
  , okay_canc_buttons_(
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel))
{
  // table selection buttons
  for (i32 i = 1; const auto& btn_txt : db_->db_txt_) {
    table_buttons_.push_back(
      std::make_unique<QPushButton>(QString::fromStdString(btn_txt)));
    layout_->addWidget(table_buttons_[i - 1].get(), 0, i - 1);
    QObject::connect(
      table_buttons_[i - 1].get(), &QPushButton::pressed, this, [this, i] {
        const DBTypes type{ i };
        switch_tables(type);
      });
    i++;
  }

  // table view
  layout_.get()->addWidget(table_view_.get(), 1, 0, 1, db_->db_txt_.size() + 1);
  table_view_->setModel(table_model_.get());
  table_view_->setSelectionBehavior(QAbstractItemView::SelectRows);
  table_view_->setSelectionMode(QAbstractItemView::MultiSelection);
  QObject::connect(table_view_->selectionModel(),
                   &QItemSelectionModel::selectionChanged,
                   this,
                   [this] { get_selected_ids(active_view_); });
  const DBTypes type{ 1 };
  switch_tables(type);

  // other buttons
  add_dataset_button_ = std::make_unique<QPushButton>("+", this);
  del_dataset_button_ = std::make_unique<QPushButton>("-", this);
  layout_.get()->addWidget(add_dataset_button_.get(), 2, 0);
  layout_.get()->addWidget(del_dataset_button_.get(), 2, 1);
  QObject::connect(add_dataset_button_.get(),
                   &QPushButton::pressed,
                   this,
                   &DatabaseViewer::add_dataset);
  QObject::connect(
    del_dataset_button_.get(), &QPushButton::pressed, this, [this] {});

  // okay / cancel button box
  layout_.get()->addWidget(
    okay_canc_buttons_.get(), 2, db_->db_txt_.size() - 1, 1, 2);
  QObject::connect(okay_canc_buttons_.get(),
                   &QDialogButtonBox::accepted,
                   this,
                   &QWidget::close);
  QObject::connect(okay_canc_buttons_.get(),
                   &QDialogButtonBox::rejected,
                   this,
                   &QWidget::close);
}

void
DatabaseViewer::switch_tables(const DBTypes db_type)
{
  if (active_view_ == db_type)
    return;

  table_model_->clear();
  add_dataset_.reset();
  active_view_ = db_type;

  switch (db_type) {
    case NONE:
      break;
    case TEXTS:
      create_table_model(table_model_.get(),
                         db_->texts_->field_names_,
                         db_->texts_->id_,
                         db_->texts_->txt_);
      break;
    case ARMIES:
      create_table_model(table_model_.get(),
                         db_->armies_->field_names_,
                         db_->armies_->id_,
                         db_->texts_->get_txts(db_->armies_->txt_id_));
      break;
    case UNITS:
      create_table_model(table_model_.get(),
                         db_->units_->field_names_,
                         db_->armies_->get_names(db_->units_->army_id_),
                         db_->units_->id_,
                         db_->texts_->get_txts(db_->units_->txt_id_));
      break;
    case MODELS:
      create_table_model(table_model_.get(),
                         db_->models_->field_names_,
                         db_->armies_->get_names(db_->models_->army_id_),
                         db_->units_->get_names(db_->models_->unit_id_),
                         db_->models_->id_,
                         db_->texts_->get_txts(db_->models_->txt_id_));
      break;
    default:
      break;
  }
  table_view_->resizeColumnsToContents();
}

void
DatabaseViewer::get_selected_ids(DBTypes db_type)
{
  switch (db_type) {
    case NONE:
      break;
    case TEXTS: {
      auto ids = extract_ids_from_selection(table_view_.get(),
                                            db_->texts_->id_table_position_);
      break;
    }
    case ARMIES: {
      auto ids = extract_ids_from_selection(table_view_.get(),
                                            db_->armies_->id_table_position_);
      break;
    }
    case UNITS: {
      auto ids = extract_ids_from_selection(table_view_.get(),
                                            db_->units_->id_table_position_);
      break;
    }
    case MODELS: {
      auto ids = extract_ids_from_selection(table_view_.get(),
                                            db_->models_->id_table_position_);
      break;
    }
    default:
      break;
  }
}

vector<i32>
DatabaseViewer::extract_ids_from_selection(const QTableView* table_view,
                                           const i32 id_position)
{
  vector<i32> result;
  for (i32 i = 0;
       auto model_index : table_view->selectionModel()->selection().indexes()) {
    i32 id = model_index.data().toInt();
    if (i == 0 || result.size() == 0 || result[i - 1] == id) {
      i++;
      continue;
    }
    result.push_back(id);
    i++;
  }
  return result;
}

void
DatabaseViewer::add_dataset()
{
  add_dataset_.reset();
  add_dataset_ = std::make_unique<AddDataset>(this, db_, active_view_);
  add_dataset_->show();
}

DatabaseViewer::~DatabaseViewer() {}
