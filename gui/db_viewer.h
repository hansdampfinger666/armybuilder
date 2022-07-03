#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QDialogButtonBox>

#include <generic/types.h>
#include <generic/qt_table.h>
#include <database/database.h>

class DatabaseViewer : public QWidget
{
  Q_OBJECT

public:
  DatabaseViewer(QWidget* parent, const DB* db);
  ~DatabaseViewer();

private:
  const DB* db_;
  QTableView* table_view_ = nullptr;
  QStandardItemModel* table_model_ = nullptr;
  QGridLayout* layout_ = nullptr;
  vector<QPushButton*> buttons_ = {};
  QDialogButtonBox* okay_canc_buttons_ = nullptr;
  DBTypes active_view_ {1};

  void switch_tables(const DBTypes db_type);
};
