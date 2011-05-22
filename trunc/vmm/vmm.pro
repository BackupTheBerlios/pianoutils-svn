QT       += core gui

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    customlcd.cpp \
    eventlistener.cpp \
    jackoutput.cpp

HEADERS  += mainwindow.h \
    customlcd.h \
    eventlistener.h \
    jackoutput.h

LIBS += -ljack

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

INSTALLS = target desktop
target.path = $$PREFIX/bin
desktop.files = VMM.desktop
desktop.path = $$PREFIX/share/applications
