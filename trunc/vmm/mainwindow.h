#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QInputDialog>
#include <QtGui/QMenu>
#include <QtGui/QActionGroup>

#include "ui_mainwindow.h"
#include "jackoutput.h"
#include "eventlistener.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setBpm();
    void clickAction(QString b);
    void hoverAction(QString b);
    void leaveAction(QString b);
    void menutriggerAction(QAction *act);

private:
    Ui::MainWindow *ui;
    int currentBpm;
    QMenu *menu;
    QActionGroup *grp;
};

#endif // MAINWINDOW_H
