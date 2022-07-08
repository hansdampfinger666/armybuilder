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
#include <generic/types.h>

#include <iostream>

class AddDataset : public QWidget
{
  Q_OBJECT

public:
  QWidget* parent = nullptr;
  AddDataset(QWidget* parent, const Db* db, const DBTypes active_view);
  ~AddDataset();

  void switch_view(const DBTypes new_view);
  
public slots: 
  void army_drop_down_changed(const QString& txt);

private:
  const Db* db_ = nullptr;
  DBTypes active_view_{ 0 };
  QGridLayout* layout_ = nullptr;
  QComboBox* army_drop_down_ = nullptr;
  QComboBox* unit_drop_down_ = nullptr;
  string army_drop_down_val_;
};
