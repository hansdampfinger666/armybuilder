#pragma once

#include <QApplication>
#include <gui/mainwindow.h>

// TODO
// - implement context aware drop down menus

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(nullptr);
  w.show();
  return a.exec();
}
