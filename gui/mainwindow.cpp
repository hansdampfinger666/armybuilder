#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Texts* texts)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , texts_(texts)
{
    ui->setupUi(this);

    QObject::connect(this->ui->pb_shut_down, &QPushButton::clicked,
                     this, &MainWindow::close);
    QObject::connect(this->ui->pb_show_texts_table, &QPushButton::clicked,
                     this, [this]{ text_table_ = new TextTable{ this, texts_ };
                                   this->text_table_->show(); });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete text_table_;
}

