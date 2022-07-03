#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , db_(new Db)
{
  ui->setupUi(this);
  db_->create_test_data();
  QObject::connect(
    this->ui->pb_master_data_maintenance, &QPushButton::clicked, this, [this] {
      database_viewer_ = new DatabaseViewer{ this, db_ };
      this->database_viewer_->show();
    });
  QObject::connect(
    this->ui->pb_shut_down, &QPushButton::clicked, this, [this]{
		delete db_;
		close();
	});
}

MainWindow::~MainWindow()
{
  delete ui;
}

