#ifndef JACKOUTPUT_H
#define JACKOUTPUT_H

#include <QObject>
#include <QTimer>
#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <math.h>
#include <stdlib.h>

//#define MAX_AMP 0.5
#define RINGBUFFER_SIZE 40000

typedef jack_default_audio_sample_t sample_t;

class JackOutput : public QObject
{
    Q_OBJECT
public:
    explicit JackOutput(QObject *parent = 0);
    ~JackOutput();
    static JackOutput* getInstance();
    int init();

signals:

public slots:
    void setBPM(int bpm);
    void setMeasure(int meas);
    float getAmp();
    void setAmp(float newAmp);


private:
    static JackOutput *instance;
    jack_client_t *client;
    jack_port_t *outPort;
    int sampleRate;
    int waveLength;
    sample_t *waveBar, *waveBeat, *waveExBar, *waveExBeat;
    jack_ringbuffer_t *rb;
    QTimer *timer;
    int currentMeasure, mCount;

    float MAX_AMP;

    void buildWave();
    static int process(jack_nframes_t frames, void *arg);

private slots:
    void click();
};

#endif // JACKOUTPUT_H
