QT       += core gui

TARGET = vmm
TARGET.path = /usr/local/bin
TARGET.files = vmm

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customlcd.cpp \
    eventlistener.cpp \
    jackoutput.cpp \
    volumewindow.cpp

HEADERS  += mainwindow.h \
    customlcd.h \
    eventlistener.h \
    jackoutput.h \
    volumewindow.h

LIBS += -ljack

FORMS    += mainwindow.ui \
    volumewindow.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS += vmm_ru_RU.ts
TRANSLATIONS.path = $$PREFIX/share/locale
TRANSLATIONS.files = vmm_ru_RU.qm

target.path = $$PREFIX/bin
desktop.files = VMM.desktop
desktop.path = $$PREFIX/share/applications

INSTALLS = target \
    TRANSLATIONS \
    desktop
