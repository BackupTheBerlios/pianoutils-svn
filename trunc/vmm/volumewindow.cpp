#include "volumewindow.h"

VolumeWindow::VolumeWindow(AudioOutput *ao, QWidget *parent) :
        QMainWindow(parent, Qt::Popup),
    ui(new Ui::VolumeWindow)
{
    ui->setupUi(this);
    output = ao;
}


void VolumeWindow::showEvent(QShowEvent *) {
    ui->verticalSlider->setSliderPosition(output->getVolume() * 100);
}

void VolumeWindow::changeVolume(int newVol) {
    output->setVolume((float) newVol / 100);
}
