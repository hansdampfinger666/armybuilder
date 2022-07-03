#pragma once 

#include <QMainWindow>

#include <gui/master_data.h>
#include <gui/db_viewer.h>
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
};
