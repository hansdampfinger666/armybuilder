#pragma once

#include <QApplication>
#include <gui/mainwindow.h>

#include <performance/performance.h>

// TODO

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(nullptr);
  w.show();
  return a.exec();
}
