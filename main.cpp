#pragma once

#include <QApplication>
#include <gui/mainwindow.h>

// TODO
// selection of rows and ids per databse now work, the gui also reacts to that
// we need to look at all consequences of a deletion of one or the other db entries again


int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(nullptr);
  w.show();
  return a.exec();
}
