#pragma once

#include <gui/mainwindow.h>
#include <QApplication>

#include <generic/test_data.h>

int main(int argc, char *argv[])
{
	auto db = new DB();
    auto test_data = new TestData(db);

    QApplication a(argc, argv);
	MainWindow w(nullptr, test_data->db_);

    w.show();
    return a.exec();
}
