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

class DatabaseViewer : public QWidget
{
  Q_OBJECT

public:
  DatabaseViewer(QWidget* parent, const Db* db);
  ~DatabaseViewer();

  void add_dataset();

private:
  QWidget* parent_ = nullptr;
  const Db* db_ = nullptr;
  QTableView* table_view_ = nullptr;
  QStandardItemModel* table_model_ = nullptr;
  QGridLayout* layout_ = nullptr;

  DBTypes active_view_{ 0 };
  vector<i32> selected_ids_;

  void switch_tables(const DBTypes db_type);
  void get_selected_ids();
  vector<i32> extract_ids_from_selection(const QTableView* table_view);
};
