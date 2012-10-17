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
    if(qtr->load("vmm_" + loc.name(), ":/translations")) a.installTranslator(qtr);

    AudioOutput ao;

    MainWindow w(&ao);

    w.show();

    return a.exec();
}
