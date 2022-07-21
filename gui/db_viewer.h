#pragma once

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

#include <database/database.h>
#include <tools/types.h>
#include <gui/add_dataset.h>
#include <guitools/qt_generate.h>

#include <tools/print.h>
#include <iostream>

class DatabaseViewer : public QWidget
{
  Q_OBJECT

public:

  struct ids_and_rows
  {
    vector<u64> ids_;
    vector<i32> rows_;
  };

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
  ids_and_rows get_selected_ids_and_rows();
  ids_and_rows extract_ids_from_selection(const QTableView* table_view,
                                         const u32 id_field_position);
};
