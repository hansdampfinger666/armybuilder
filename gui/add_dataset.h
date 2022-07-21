#pragma once

#include <QAction>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QWidget>

#include <QComboBox>
#include <QLabel>

#include <database/database.h>
#include <tools/print.h>
#include <tools/types.h>
#include <guitools/qt_generate.h>

#include <iostream>

class AddDataset : public QWidget
{
  Q_OBJECT

public:
  QWidget* parent = nullptr;
  AddDataset(QWidget* parent, const Db* db, const DBTypes active_view);
  ~AddDataset();

signals:
  void added_db_entry(const u64 id);

public slots:
  void army_drop_down_changed(const QString& txt);
  void commit_changes();

private:
  const Db* db_ = nullptr;
  DBTypes active_view_{ 0 };
  QGridLayout* layout_ = nullptr;
  QComboBox* army_drop_down_ = nullptr;
  QComboBox* unit_drop_down_ = nullptr;
  string army_drop_down_val_;
  
  vector<QLineEdit*> data_edit_;

  void switch_view(const DBTypes new_view);
  void set_window_title(const DBTypes new_view);
};
