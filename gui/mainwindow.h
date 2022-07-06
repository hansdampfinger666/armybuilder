#pragma once 

#include <QMainWindow>

#include <gui/db_viewer.h>
#include <gui/add_dataset.h>
#include <database/database.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	DatabaseViewer* database_viewer_;
	Db* db_;
    Texts* texts_;
    Armies* armies_;
    Units* units_;
    Models* models_;

		QPushButton* test_pushbutton_ = nullptr;
		AddDataset* add_dataset_ = nullptr;
};
