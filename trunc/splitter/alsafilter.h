#ifndef ALSAFILTER_H
#define ALSAFILTER_H

#include <QThread>
#include <alsa/asoundlib.h>

class AlsaFilter : public QThread
{
    Q_OBJECT
public:
    explicit AlsaFilter(QObject *parent = 0);

protected:
    void run();

private:
    int inport, outport;
    snd_seq_t *seq;
    int currentNote;
    int ch1Num, ch2Num;
    int ch1Shift, ch2Shift;

signals:

public slots:
    void setNote(int i);
    void setChNum1(int num);
    void setChNum2(int num);
    void setChShift1(int notes);
    void setChShift2(int notes);
};

#endif // ALSAFILTER_H
