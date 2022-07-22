#pragma once

#include <QApplication>
#include <gui/mainwindow.h>

// TODO
// switched to i32 -> maybe bugs as a result? size_t != i32
// feature: update existing datasets
// housekeeping: codify mainwindow GUI as well

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(nullptr);
  w.show();
  return a.exec();
}

// NOTES
// keeping dead data around in structure of arrays:
//		keeping "dead" (id == 0) data sets around in the databases seems 
//		like a good idea at first, to avoid erasing and reallocating vector 
//		elements; but why it's actually a shite iea: deleting data sets is a 
//		rare occurrence we are doing the following things way more often:
//		1. traversing and searching our databases -> having dead data
//			littering our databases is bad
//		2. we are adding way more than we are deleting
//		--> make important things fast, keep our expected data in mind
//	--> erase implemented in all DB
