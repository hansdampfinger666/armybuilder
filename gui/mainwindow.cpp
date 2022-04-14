#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Texts* texts, Armies* armies)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , texts_(texts)
    , armies_(armies)
{
    ui->setupUi(this);

    QObject::connect(this->ui->pb_shut_down, &QPushButton::clicked,
                     this, &MainWindow::close);
    QObject::connect(this->ui->pb_master_data_maintenance,
                     &QPushButton::clicked,
                     this, [this]{ master_data_table_ =
                                new MasterData{ nullptr, texts_ };
                                this->master_data_table_->show(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

