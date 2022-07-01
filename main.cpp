#pragma once

#include <gui/mainwindow.h>
#include <QApplication>

#include <generic/test_data.h>

int main(int argc, char *argv[])
{
	std::cout << "this is a test of the console from main\n";

	auto db = new class db();
    auto test_data = new TestData(db);

    QApplication a(argc, argv);
	MainWindow w(nullptr, test_data->db_);

//    MainWindow w(nullptr, test_data->texts_, test_data->armies_,
//                 test_data->units_, test_data->models_);

    w.show();
    return a.exec();
}
