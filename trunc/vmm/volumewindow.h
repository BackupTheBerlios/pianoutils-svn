#ifndef VOLUMEWINDOW_H
#define VOLUMEWINDOW_H

#include <QMainWindow>

#include "ui_volumewindow.h"
#include "audiooutput.h"

namespace Ui {
    class VolumeWindow;
}

class VolumeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit VolumeWindow(AudioOutput *ao, QWidget *parent = 0);

signals:

public slots:
    void changeVolume(int newVol);

protected:
    void showEvent(QShowEvent *);

private:
    Ui::VolumeWindow *ui;
    AudioOutput *output;
};

#endif // VOLUMEWINDOW_H
