#pragma once

#include <QApplication>
#include <gui/mainwindow.h>

// TODO
// implement adding new data sets in DatabaseViewer

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(nullptr);
  w.show();
  return a.exec();
}
