QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += \
            -std=c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	performance/performance.cpp \
	disk_io/csv.cpp \
  database/army.cpp \
	database/database.cpp \
  database/unit.cpp \
  database/model.cpp \
	database/abstract_database.cpp \
	guitools/qt_generate.cpp \
  gui/mainwindow.cpp \
  gui/db_viewer.cpp \
	gui/add_dataset.cpp \
  main.cpp

HEADERS += \
	performance/performance.h \
	disk_io/csv.h \
  disk_io/serialize.h \
  database/army.h \
  database/database.h \
  database/unit.h \
  database/model.h \
	database/abstract_database.h \
  tools/print.h \
  tools/types.h \
  tools/vec_ops.h \
	tools/conversions.h \
  guitools/qt_conversions.h \
	guitools/qt_generate.h \
  gui/mainwindow.h \
  gui/db_viewer.h \
	gui/add_dataset.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
