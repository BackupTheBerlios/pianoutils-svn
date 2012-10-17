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

!contains (DEFINES, __SPLITTER_WITHOUTJACK__) {
    SOURCES += jackfilter.cpp
    HEADERS += jackfilter.h
    LIBS += -ljack
}

TRANSLATIONS += splitter_ru_RU.ts
TRANSLATIONS.files = splitter_ru_RU.qm

target.path = $$PREFIX/bin
desktop.files = splitter.desktop
desktop.path = $$PREFIX/share/applications

INSTALLS += target \
    desktop

RESOURCES += \
    resources.qrc
