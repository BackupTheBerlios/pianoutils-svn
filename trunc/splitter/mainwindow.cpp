#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->inputChCombo->addItem(tr("All"));
    ui->nw->setValue(36);
    for (int i = 1; i < 17; i++) {
        ui->channel1Combo->addItem(QString("%1").arg(i));
        ui->channel2Combo->addItem(QString("%1").arg(i));
        ui->inputChCombo->addItem(QString("%1").arg(i));
    }
    ui->channel2Combo->setCurrentIndex(1);

    // ALSA filter
    filter = new AlsaFilter();
    filter->start();
    connect(ui->nw, SIGNAL(valueChanged(int)), filter, SLOT(setNote(int)));
    connect(ui->channel2Combo, SIGNAL(currentIndexChanged(int)), filter, SLOT(setChNum2(int)));
    connect(ui->channel1Combo, SIGNAL(currentIndexChanged(int)), filter, SLOT(setChNum1(int)));
    connect(ui->channel1Spin, SIGNAL(valueChanged(int)), filter, SLOT(setChShift1(int)));
    connect(ui->channel2Spin, SIGNAL(valueChanged(int)), filter, SLOT(setChShift2(int)));
    connect(ui->inputChCombo, SIGNAL(currentIndexChanged(int)), filter, SLOT(setChFilter(int)));

    // Jack filter
    try {
        jFilter = new JackFilter();
        connect(ui->nw, SIGNAL(valueChanged(int)), jFilter, SLOT(setNote(int)));
        connect(ui->channel1Combo, SIGNAL(currentIndexChanged(int)), jFilter, SLOT(setChNum1(int)));
        connect(ui->channel2Combo, SIGNAL(currentIndexChanged(int)), jFilter, SLOT(setChNum2(int)));
        connect(ui->channel1Spin, SIGNAL(valueChanged(int)), jFilter, SLOT(setChShift1(int)));
        connect(ui->channel2Spin, SIGNAL(valueChanged(int)), jFilter, SLOT(setChShift2(int)));
        connect(ui->inputChCombo, SIGNAL(currentIndexChanged(int)), jFilter, SLOT(setChFilter(int)));
    } catch(int e) {
        QMessageBox::warning(this, tr("Jack error"), tr("Can't connect to jack server"));
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}
