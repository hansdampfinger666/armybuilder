#pragma once

#include <gui/mainwindow.h>
#include <QApplication>

// TODO 
// - implement context aware drop down menus, that react to dependent field values, maybe make it fully dynamic?
// - clean up vec_ops redundancy and beautify the code

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MainWindow w(nullptr);
    w.show();
        return a.exec();
}
