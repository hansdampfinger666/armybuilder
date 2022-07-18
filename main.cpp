#pragma once

#include <QApplication>
#include <gui/mainwindow.h>

#include <performance/performance.h>

// TODO
// the initial dependent drop down menus when adding datasets do not work properly
// 	they show nothing, not the correct dependent value
// 	after resetting them by choosing a value manually, they work fine

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(nullptr);
  w.show();
  return a.exec();
}
