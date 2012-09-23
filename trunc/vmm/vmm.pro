QT       += core gui

TARGET = vmm
TARGET.path = /usr/local/bin
TARGET.files = vmm

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customlcd.cpp \
    eventlistener.cpp \
    volumewindow.cpp \
    audiooutput.cpp

HEADERS  += mainwindow.h \
    customlcd.h \
    eventlistener.h \
    volumewindow.h \
    audiooutput.h

LIBS += -ljack -lrtaudio

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
