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

INSTALLS += target desktop
target.path = $$PREFIX/bin
desktop.files = splitter.desktop
desktop.path = $$PREFIX/share/applications
