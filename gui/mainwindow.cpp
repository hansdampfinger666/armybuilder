#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, DB* db)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, db_(db)
{
    ui->setupUi(this);

    QObject::connect(this->ui->pb_shut_down, &QPushButton::clicked,
                     this, &MainWindow::close);

	QObject::connect(this->ui->pb_master_data_maintenance,
                     &QPushButton::clicked,
                     this, [this]{ database_viewer_ =
                                new DatabaseViewer{ this, db_ };
                                this->database_viewer_->show(); });
}

MainWindow::MainWindow(QWidget *parent, Texts* texts, Armies* armies,
                       Units* units, Models* models)
    : QMainWindow(parent)
	, ui(new Ui::MainWindow)
    , texts_(texts)
    , armies_(armies)
    , units_(units)
    , models_(models)
{
    ui->setupUi(this);

    QObject::connect(this->ui->pb_shut_down, &QPushButton::clicked,
                     this, &MainWindow::close);

	QObject::connect(this->ui->pb_master_data_maintenance,
                     &QPushButton::clicked,
                     this, [this]{ master_data_table_ =
                                new MasterData{ nullptr, texts_,
                                armies_, units_, models_ };
                                this->master_data_table_->show(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

