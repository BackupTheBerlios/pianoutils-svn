#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "mainwindow.h"
#include "audiooutput.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator *qtr = new QTranslator(0);
    QLocale loc;
    QString locPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    if(qtr->load("vmm_" + loc.name(), locPath)) a.installTranslator(qtr);
    else {
        locPath = "/usr/local/share/locale";
        qtr->load("vmm_" + loc.name(), locPath);
        a.installTranslator(qtr);
    }

    AudioOutput ao;

    MainWindow w(&ao);

    /*JackOutput *jo = JackOutput::getInstance();
    jo->init();*/

    w.show();

    return a.exec();
}
