#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gui/text_table.h>

#include <database/text.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Texts* texts = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TextTable *text_table_;

    Texts* texts_;
};
#endif // MAINWINDOW_H
