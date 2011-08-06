QT       += core gui

TARGET = splitter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    alsafilter.cpp \
    notewidget.cpp \
    jackfilter.cpp

HEADERS  += mainwindow.h \
    alsafilter.h \
    notewidget.h \
    jackfilter.h

FORMS    += mainwindow.ui

LIBS += -lasound -ljack

INSTALLS += target
target.path = $$PREFIX/bin
