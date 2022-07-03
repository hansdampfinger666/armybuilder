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

class DatabaseViewer : public QWidget
{
  Q_OBJECT

public:
  DatabaseViewer(QWidget* parent, const Db* db);
  ~DatabaseViewer();

private:
  const Db* db_;
  QTableView* table_view_ = nullptr;
  QStandardItemModel* table_model_ = nullptr;
  QGridLayout* layout_ = nullptr;
  vector<QPushButton*> buttons_ = {};
  QDialogButtonBox* okay_canc_buttons_ = nullptr;

  DBTypes active_view_{ 0 };
  vector<i32> selected_ids_;

  void switch_tables(const DBTypes db_type);
  void get_selected_ids(const DBTypes db_type);
  vector<i32> extract_ids_from_selection(const QTableView* table_view, const i32 id_position);
  void add_dataset();
  void delete_datasets();
};
