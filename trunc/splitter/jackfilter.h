#ifndef JACKFILTER_H
#define JACKFILTER_H

#include <jack/jack.h>
#include <jack/midiport.h>
#include <string.h>
#include <QObject>

typedef struct {
    jack_port_t *inPort, *outPort;
    int currentNote;
    int channelFilter;
    int ch1Num, ch2Num, ch1Shift, ch2Shift;
} data;


class JackFilter : public QObject
{
    Q_OBJECT

public:
    explicit JackFilter(QObject *parent = 0);
    ~JackFilter();

public slots:
    void setNote(int i);
    void setChFilter(int chnl);
    void setChNum1(int num);
    void setChNum2(int num);
    void setChShift1(int notes);
    void setChShift2(int notes);

private:
    jack_client_t *client;
    data par;
};

#endif // JACKFILTER_H
