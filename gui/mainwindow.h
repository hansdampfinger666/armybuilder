#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gui/master_data.h>

#include <database/database.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,
               Texts* texts = nullptr,
               Armies* armies = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MasterData *master_data_table_;

    Texts* texts_;
    Armies* armies_;
};
#endif // MAINWINDOW_H
