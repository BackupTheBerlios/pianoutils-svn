#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

#include <RtAudio.h>
#include <QHash>
#include <QVector>
#include <QString>
#include <QTimer>
#include <QObject>
#include <vector>
#include <string>
#include <math.h>

#define CLICK_LENGTH 0.2

typedef struct {
    int apiId;
    int deviceId;
    QString label;
} DeviceInformation;

typedef struct {
    unsigned long currentI; // Number of current wave sample
    float frameRatio;       // Constant 2PI/samplerate
    bool isClickProcessing; // If flag is TRUE play sound
    float *envelope;        // Samples array used for envelope
    int clickLength;        // Length of sound (in samples)
    float currentVolume;    // Amplification coefficient
    int mCount;             // Bar/beats counter
} UserData;


class AudioOutput : public QObject
{
    Q_OBJECT
public:
    AudioOutput(QObject *parent = 0);
    ~AudioOutput();
    QVector <QString> getDevices();
    QString setOutputDevice(int id);
    void setBPM(int bpm);
    void setMeasure(int meas);
    void setVolume(float vol);
    float getVolume();

private:
    QHash <int, RtAudio *> interfaces;  // Keeps instances of all compiled APIs
    QVector <DeviceInformation> dd;     // All available devices
    int currentAPI;                     // Activated API id
    int currentBPM;
    int currentMeasure;
    QTimer *timer;                      // Beat timer
    UserData data;                      // Variable for communication between class and callback function

private slots:
    void click();
};


int outCallback(void *outputBuffer, void *inputBuffer, unsigned int nFrames,
                double streamTime, RtAudioStreamStatus status, void *ud);

#endif // AUDIOOUTPUT_H
