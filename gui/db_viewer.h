#pragma once

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

#include <database/database.h>
#include <generic/types.h>
#include <gui/add_dataset.h>
#include <guitools/qt_generate.h>

#include <generic/print.h>
#include <iostream>

class DatabaseViewer : public QWidget
{
  Q_OBJECT

public:
  DatabaseViewer(QWidget* parent, const Db* db);
  ~DatabaseViewer();

  public slots:
	  void fetch_new_db_entry(const u64 id);

private:
  QWidget* parent_ = nullptr;
  const Db* db_ = nullptr;
  QTableView* table_view_ = nullptr;
  QStandardItemModel* table_model_ = nullptr;
  QGridLayout* layout_ = nullptr;

  DBTypes active_view_{ 0 };
  vector<i32> selected_ids_;

  void switch_tables(const DBTypes db_type);
  void set_window_title(const DBTypes new_view);
  void add_dataset();
	void delete_datasets();
  void get_selected_ids();
  vector<i32> extract_ids_from_selection(const QTableView* table_view);
};
