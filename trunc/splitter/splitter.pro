QT       += core gui

TARGET = splitter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    alsafilter.cpp \
    notewidget.cpp

HEADERS  += mainwindow.h \
    alsafilter.h \
    notewidget.h

FORMS    += mainwindow.ui

LIBS += -lasound

INSTALLS += target
target.path = $$PREFIX/bin
