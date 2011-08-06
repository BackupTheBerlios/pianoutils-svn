#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "alsafilter.h"
#include "jackfilter.h"
#include "notewidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AlsaFilter *filter;
    JackFilter *jFilter;
    NoteWidget *nw;
};

#endif // MAINWINDOW_H
