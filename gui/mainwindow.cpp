#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , db_(new Db)
{
  db_->create_test_data();

  // gui setup
  ui->setupUi(this);
  this->setWindowTitle("Armybuilder 2000");
  QObject::connect(
    this->ui->pb_master_data_maintenance, &QPushButton::clicked, this, [this] {
      database_viewer_ = new DatabaseViewer{ this, db_ };
      this->database_viewer_->show();
    });
  QObject::connect(this->ui->pb_shut_down, &QPushButton::clicked, this, [this] {
    delete db_;
    close();
  });

  test_pushbutton_ = new QPushButton("Test Button", this);
  QObject::connect(test_pushbutton_, &QPushButton::pressed, this, [this] {
    DBTypes active_view{ 1 };
    add_dataset_ = new AddDataset(this, db_, active_view);
    add_dataset_->show();
  });
}

MainWindow::~MainWindow()
{
  delete ui;
}
