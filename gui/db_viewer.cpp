#include "db_viewer.h"
#include "guitools/qt_generate.h"

DatabaseViewer::DatabaseViewer(QWidget* parent, const Db* db)
  : parent_(parent)
  , db_(db)
  , table_view_(new QTableView(this))
  , table_model_(new QStandardItemModel(this))
  , layout_(new QGridLayout(this))
{
  // table selection buttons
  for (i32 i = 1; const auto& btn_txt : db_->db_txt_) {
    auto btn = new QPushButton(QString::fromStdString(btn_txt), this);
    layout_->addWidget(btn, 0, i - 1);
    QObject::connect(btn, &QPushButton::pressed, this, [this, i] {
      const DBTypes type{ i };
      switch_tables(type);
    });
    i++;
  }

  // table view
  layout_->addWidget(table_view_, 1, 0, 1, db_->db_txt_.size() + 1);
  table_view_->setModel(table_model_);
  table_view_->setSelectionBehavior(QAbstractItemView::SelectRows);
  table_view_->setSelectionMode(QAbstractItemView::MultiSelection);
  QObject::connect(table_view_->selectionModel(),
                   &QItemSelectionModel::selectionChanged,
                   this,
                   &DatabaseViewer::get_selected_ids);
  QObject::connect(table_model_,
                   &QStandardItemModel::rowsInserted,
                   table_view_,
                   &QTableView::scrollToBottom);
  const DBTypes type{ 1 };
  switch_tables(type);

  // other buttons
  auto add_dataset_button = new QPushButton("+", this);
  auto del_dataset_button = new QPushButton("-", this);
  layout_->addWidget(add_dataset_button, 2, 0);
  layout_->addWidget(del_dataset_button, 2, 1);
  QObject::connect(add_dataset_button,
                   &QPushButton::clicked,
                   this,
                   &DatabaseViewer::add_dataset);
  QObject::connect(del_dataset_button,
                   &QPushButton::clicked,
                   this,
                   &DatabaseViewer::delete_datasets);

  // okay / cancel button box
  auto okay_canc_buttons =
    new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
  layout_->addWidget(okay_canc_buttons, 2, db_->db_txt_.size() - 1, 1, 2);
  QObject::connect(
    okay_canc_buttons, &QDialogButtonBox::accepted, this, &QWidget::close);
  QObject::connect(
    okay_canc_buttons, &QDialogButtonBox::rejected, this, &QWidget::close);
}

void
DatabaseViewer::set_window_title(const DBTypes new_view)
{
  auto title =
    QString::fromStdString({ "Database: " + db_->db_txt_[new_view - 1] });
  this->setWindowTitle(title);
}

void
DatabaseViewer::switch_tables(const DBTypes db_type)
{
  if (active_view_ == db_type)
    return;

  table_model_->clear();
  active_view_ = db_type;
  set_window_title(active_view_);

  switch (db_type) {
    case NONE:
      break;
    case TEXTS:
      qt_generate::create_table_model(table_model_,
                                      db_->texts_->field_names_,
                                      db_->texts_->id_,
                                      db_->texts_->txt_);
      break;
    case ARMIES:
      qt_generate::create_table_model(
        table_model_,
        db_->armies_->field_names_,
        db_->armies_->id_,
        db_->texts_->get_names(db_->armies_->txt_id_));
      break;
    case UNITS:
      qt_generate::create_table_model(
        table_model_,
        db_->units_->field_names_,
        db_->armies_->get_names(db_->units_->army_id_),
        db_->units_->id_,
        db_->texts_->get_names(db_->units_->txt_id_));
      break;
    case MODELS:
      qt_generate::create_table_model(
        table_model_,
        db_->models_->field_names_,
        db_->armies_->get_names(db_->models_->army_id_),
        db_->units_->get_names(db_->models_->unit_id_),
        db_->models_->id_,
        db_->texts_->get_names(db_->models_->txt_id_));
      break;
    default:
      break;
  }
  table_view_->resizeColumnsToContents();
}

void
DatabaseViewer::add_dataset()
{
  auto add_dataset = new AddDataset(this, db_, active_view_);
  QObject::connect(add_dataset,
                   &AddDataset::added_db_entry,
                   this,
                   &DatabaseViewer::fetch_new_db_entry);
  add_dataset->show();
}

void
DatabaseViewer::fetch_new_db_entry(const u64 id)
{
  switch (active_view_) {
    case NONE:
      break;
    case TEXTS: {
      auto text = db_->texts_->get(id);
      if (!text)
        return;
      qt_generate::append_row(
        table_model_, text.value().id_, text.value().txt_);
      break;
    }
    case ARMIES: {
      auto army = db_->armies_->get_readable(id);
      if (!army)
        return;
      qt_generate::append_row(
        table_model_, army.value().id_, army.value().txt_);
      break;
    }
    case UNITS: {
      auto unit = db_->units_->get_readable(id);
      if (!unit)
        return;
      qt_generate::append_row(table_model_,
                              unit.value().army_txt_,
                              unit.value().id_,
                              unit.value().txt_);
      break;
    }
    case MODELS: {
      auto model = db_->models_->get_readable(id);
      if (!model)
        return;
      qt_generate::append_row(table_model_,
                              model->army_txt_,
                              model->unit_txt_,
                              model->id_,
                              model->txt_);
      break;
    }
    default:
      break;
  }
  table_view_->resizeColumnsToContents();
}

void
DatabaseViewer::get_selected_ids()
{
  switch (active_view_) {
    case NONE:
      break;
    case TEXTS: {
      auto ids = extract_ids_from_selection(table_view_);
      break;
    }
    case ARMIES: {
      auto ids = extract_ids_from_selection(table_view_);
      break;
    }
    case UNITS: {
      auto ids = extract_ids_from_selection(table_view_);
      break;
    }
    case MODELS: {
      auto ids = extract_ids_from_selection(table_view_);
      break;
    }
    default:
      break;
  }
}

vector<i32>
DatabaseViewer::extract_ids_from_selection(const QTableView* table_view)
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
DatabaseViewer::delete_datasets()
{
	auto tab = new PrintTable(extract_ids_from_selection(table_view_));
}

DatabaseViewer::~DatabaseViewer() {}
