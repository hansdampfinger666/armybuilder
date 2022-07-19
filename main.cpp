#pragma once

#include <QApplication>
#include <gui/mainwindow.h>

#include <performance/performance.h>

// TODO
// selection of rows and ids per databse now work, the gui also reacts to that
// we need to look at all consequences of a deletion of one or the other db entries again
// part of that: directly deleting texts whould not really be possible, since the are more like
// share pointers, they don't decide if they live or die, other guys do as long as they refer to them
// maybe fix that

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(nullptr);
  w.show();
  return a.exec();
}
