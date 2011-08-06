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

TRANSLATIONS += splitter_ru_RU.ts
TRANSLATIONS.path = $$PREFIX/share/locale
TRANSLATIONS.files = splitter_ru_RU.qm

target.path = $$PREFIX/bin
desktop.files = splitter.desktop
desktop.path = $$PREFIX/share/applications

INSTALLS += target \
    TRANSLATIONS \
    desktop