#include "audiooutput.h"

AudioOutput::AudioOutput(QObject *parent) : QObject(parent), currentAPI(-1), currentBPM(120) {
    // Create object instances for all available APIs
    std::vector <RtAudio::Api> apis;
    RtAudio::getCompiledApi(apis);
    for (unsigned int i = 0; i < apis.size(); i++)
        interfaces.insert(apis[i], new RtAudio(apis[i]));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(click()));
    setBPM(120);
    data.envelope = NULL;
    data.currentVolume = 0.5;
    data.mCount = 0;
}


AudioOutput::~AudioOutput() {};

/*
 * Fills data about all available output devices and returns name list
 */
QVector <QString> AudioOutput::getDevices() {
    QVector <QString> ret;
    QHashIterator <int, RtAudio *> i(interfaces);
    while (i.hasNext()) {
        QString pref;

        i.next();        
        switch(i.key()) {
        case RtAudio::LINUX_ALSA:
            pref = "ALSA: ";
            break;
        case RtAudio::UNIX_JACK:
            pref = "Jack: ";
            break;
        }

        for (unsigned int j = 0; j < i.value()->getDeviceCount(); j++) {
            RtAudio::DeviceInfo info = i.value()->getDeviceInfo(j);
            if (info.outputChannels > 0) {
                DeviceInformation di;
                di.label = pref + QString(info.name.c_str());
                di.apiId = i.key();
                di.deviceId = j;
                dd.append(di);
                ret.append(di.label);
            }
        }
    }
    return ret;
}


/*
 * Set new output device.
 */
QString AudioOutput::setOutputDevice(int id) {
    unsigned int bufFrames = 256, sampleRate;
    RtAudio::StreamParameters p;
    RtAudio *obj;

    // Deactivate previous device
    if (currentAPI != -1) {
        obj = interfaces[currentAPI];
        try {
            obj->stopStream();
        } catch (RtError &e) {
            return QString(e.getMessage().c_str());
        }
        if (obj->isStreamOpen()) obj->closeStream();
    }

    currentAPI = dd[id].apiId;
    obj = interfaces[currentAPI];

    RtAudio::DeviceInfo info = obj->getDeviceInfo(dd[id].deviceId);

    // Use new device
    p.deviceId = dd[id].deviceId;
    p.nChannels = 1;
    p.firstChannel = 0;
    sampleRate = info.sampleRates[0];
    data.currentI = 0;
    data.frameRatio = 2 * M_PI / (float) info.sampleRates[0];

    try {
        obj->openStream(&p, NULL, RTAUDIO_FLOAT64, sampleRate, &bufFrames,
                        &outCallback, &data);
        obj->startStream();
    } catch (RtError &e) {
        return QString(e.getMessage().c_str());
    }

    // Create envelope
    data.clickLength = info.sampleRates[0] / 10;
    int attackLength = data.clickLength / 100;
    int decayLength = data.clickLength / 10;
    if (data.envelope != NULL) free(data.envelope);
    data.envelope = (float *) malloc(sizeof(float) * data.clickLength);

    for (int i = 0; i < attackLength; i++)
        data.envelope[i] = i / (float) attackLength;
    for (int i = attackLength; i < data.clickLength - decayLength; i++)
        data.envelope[i] = 1.0;
    for (int i = data.clickLength - decayLength; i < data.clickLength; i++)
    data.envelope[i] = -((float) i - (float) data.clickLength) / decayLength;
    data.isClickProcessing = false;

    return QString("");
}


/*
 * Set metronome Beat per Minute
 */
void AudioOutput::setBPM(int bpm) {
    timer->stop();
    data.isClickProcessing = false;
    timer->start(1000.0 / (bpm / 60.0));
}


/*
 * Raised by timer event
 */
void AudioOutput::click() {
    data.isClickProcessing = true;
    if (data.mCount == currentMeasure) data.mCount = 0;
    else data.mCount++;
}


/*
 * Audio output loop processing
 */
int outCallback(void *outputBuffer, void *inputBuffer, unsigned int nFrames,
                double streamTime, RtAudioStreamStatus status, void *ud) {
    double *buffer = (double *) outputBuffer;
    UserData *data = (UserData *) ud;
    float freq;

    memset(buffer, 0, sizeof(double) * nFrames);

    if (data->mCount == 0) freq = 1100.0;
    else freq = 880.0;

    if (data->isClickProcessing) {
        int j;
        if (data->clickLength - data->currentI >= nFrames) j = nFrames;
        else j = data->clickLength - data->currentI;
        for (int i = 0; i < j; i++, data->currentI++)
            buffer[i] = data->currentVolume * data->envelope[data->currentI] * sinf(data->frameRatio * freq * (float) (data->currentI));
   }

    if (data->currentI >= data->clickLength) {
        data->isClickProcessing = false;
        data->currentI = 0;
    }
}


/*
 *
 */
void AudioOutput::setVolume(float vol) {
    data.currentVolume = vol;
}


/*
 *
 */
float AudioOutput::getVolume() {
    return data.currentVolume;
}


/*
 *
 */
void AudioOutput::setMeasure(int meas) {
    currentMeasure = meas;
    data.mCount = 0;
    data.currentI = 0;
}
