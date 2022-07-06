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
  AddDataset(QWidget* parent, const Db* db, const DBTypes active_view);
  ~AddDataset();

private:
  const Db* db_ = nullptr;
  DBTypes active_view_{ 0 };
  QGridLayout* layout_ = nullptr;
  QDialogButtonBox* okay_canc_buttons_ = nullptr;

  vector<QLabel*> labels_;
  QComboBox* army_drop_down_ = nullptr;

  void switch_view(const DBTypes new_view);
};