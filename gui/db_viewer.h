#pragma once

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

#include <database/database.h>
#include <generic/qt_table.h>
#include <generic/types.h>
#include <gui/add_dataset.h>

#include <memory>

class DatabaseViewer : public QWidget
{
  Q_OBJECT

public:
  DatabaseViewer(QWidget* parent, const Db* db);
  ~DatabaseViewer();

  void add_dataset();

private:
  const Db* db_;
  uptr<QTableView> table_view_ = nullptr;
  uptr<QStandardItemModel> table_model_ = nullptr;
  uptr<QGridLayout> layout_ = nullptr;
  vector<uptr<QPushButton>> table_buttons_ = {};
  uptr<QPushButton> add_dataset_button_ = nullptr;
  uptr<QPushButton> del_dataset_button_ = nullptr;
  uptr<QDialogButtonBox> okay_canc_buttons_ = nullptr;
  uptr<AddDataset> add_dataset_ = nullptr;

  DBTypes active_view_{ 0 };
  vector<i32> selected_ids_;

  void switch_tables(const DBTypes db_type);
  void get_selected_ids(const DBTypes db_type);
  vector<i32> extract_ids_from_selection(const QTableView* table_view, const i32 id_position);
};
