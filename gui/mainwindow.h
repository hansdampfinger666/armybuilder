#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
	MainWindow(QWidget *parnet = nullptr,
			db* db = nullptr);
    MainWindow(QWidget *parent = nullptr,
               Texts* texts = nullptr,
               Armies* armies = nullptr,
               Units* units = nullptr,
               Models* models = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MasterData *master_data_table_;
	DatabaseViewer* database_viewer_;

	db* db_;

    Texts* texts_;
    Armies* armies_;
    Units* units_;
    Models* models_;
};
#endif // MAINWINDOW_H
