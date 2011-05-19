#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filter = new AlsaFilter();
    filter->start();
    //nw = new NoteWidget(this);
    ui->nw->setValue(36);
    connect(ui->nw, SIGNAL(valueChanged(int)), filter, SLOT(setNote(int)));

    for(int i = 1; i < 17; i++) ui->channel2Combo->addItem(QString("%1").arg(i));
    ui->channel2Combo->setCurrentIndex(1);
    connect(ui->channel2Combo, SIGNAL(currentIndexChanged(int)), filter, SLOT(setChNum2(int)));
    for(int i = 1; i < 17; i++) ui->channel1Combo->addItem(QString("%1").arg(i));
    connect(ui->channel1Combo, SIGNAL(currentIndexChanged(int)), filter, SLOT(setChNum1(int)));
    connect(ui->channel1Spin, SIGNAL(valueChanged(int)), filter, SLOT(setChShift1(int)));
    connect(ui->channel2Spin, SIGNAL(valueChanged(int)), filter, SLOT(setChShift2(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
