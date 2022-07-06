QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += \
            -std=c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database/army.cpp \
    database/text.cpp \
	database/database.cpp \
    database/unit.cpp \
    database/model.cpp \
    gui/mainwindow.cpp \
    gui/db_viewer.cpp \
	gui/add_dataset.cpp \
    main.cpp

HEADERS += \
    database/army.h \
    database/database.h \
    database/text.h \
    database/unit.h \
    database/model.h \
    generic/print.h \
    generic/qt_conversions.h \
    generic/qt_table.h \
    generic/serialize.h \
    generic/test_data.h \
    generic/types.h \
    generic/vec_ops.h \
    gui/mainwindow.h \
    gui/db_viewer.h \
	gui/add_dataset.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
