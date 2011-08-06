#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator *qtr = new QTranslator(0);
    QLocale loc;
    QString locPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    if(qtr->load("splitter_" + loc.name(), locPath)) a.installTranslator(qtr);
    else {
            locPath = "/usr/local/share/locale";
            qtr->load("splitter_" + loc.name(), locPath);
            a.installTranslator(qtr);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
