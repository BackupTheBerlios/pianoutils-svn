#include "volumewindow.h"

VolumeWindow::VolumeWindow(QWidget *parent) :
        QMainWindow(parent, Qt::Popup),
    ui(new Ui::VolumeWindow)
{
    ui->setupUi(this);
}


void VolumeWindow::showEvent(QShowEvent *) {
    ui->verticalSlider->setSliderPosition(JackOutput::getInstance()->getAmp() * 100);
    //emit signalMainWindowShown();
}

void VolumeWindow::changeVolume(int newVol) {
    JackOutput::getInstance()->setAmp((float) newVol / 100);
}
