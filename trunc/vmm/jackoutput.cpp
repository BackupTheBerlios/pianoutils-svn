#include "jackoutput.h"
#include <stdio.h>

JackOutput* JackOutput::instance = 0;

JackOutput::JackOutput(QObject *parent) : QObject(parent), MAX_AMP(0.5) {
}


JackOutput::~JackOutput() {
    jack_ringbuffer_free(rb);
    jack_client_close(client);
}


JackOutput *JackOutput::getInstance() {
    if (instance == 0) instance = new JackOutput();
    return instance;
}


int JackOutput::init() {
    if ((client = jack_client_open("vmm", (jack_options_t) 0, NULL)) == 0)
        return -1;

    outPort = jack_port_register(client, "bpm", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    sampleRate = jack_get_sample_rate(client);

    buildWave();
    jack_set_process_callback(client, JackOutput::getInstance()->process, NULL);
    rb = jack_ringbuffer_create(RINGBUFFER_SIZE);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(click()));
    setBPM(120);

    if (jack_activate(client)) return -2;

    return 0;
}


void JackOutput::setBPM(int bpm) {
    timer->stop();
    timer->start(1000.0 / (bpm / 60.0));
}


void JackOutput::setMeasure(int meas) {
    currentMeasure = meas;
    mCount = 0;
}


void JackOutput::buildWave() {
    double *amp;
    sample_t scale, scaleA;
    int attackLength, decayLength, i;

    waveLength = sampleRate / 10;
    attackLength = waveLength / 100;
    decayLength = waveLength / 10;
    scale = 2 * M_PI * 880 / sampleRate;
    scaleA = 2 * M_PI *1100 / sampleRate;

    waveExBar = (sample_t *) malloc(waveLength * sizeof(sample_t));
    waveExBeat = (sample_t *) malloc(waveLength * sizeof(sample_t));
    waveBar = (sample_t *) malloc(waveLength * sizeof(sample_t));
    waveBeat = (sample_t *) malloc(waveLength * sizeof(sample_t));
    amp = (double *) malloc(waveLength * sizeof(double));

    for (i = 0; i < attackLength; i++)
        amp[i] = i / (double) attackLength;

    for (i = attackLength; i < (int) waveLength - decayLength; i++)
        amp[i] = 1;

    for (i = (int) waveLength - decayLength; i < (int) waveLength; i++) {
        amp[i] = - (i - (double) waveLength) / (double) decayLength;
    }

    for (i = 0; i < (int) waveLength; i++) {
        waveExBar[i] = amp[i] * sin(scaleA * i);
        waveExBeat[i] =  amp[i] * sin(scale * i);
    }

    setAmp(MAX_AMP);
}


int JackOutput::process(jack_nframes_t frames, void *arg) {
    JackOutput *j = JackOutput::getInstance();

    sample_t *buffer = (sample_t *) jack_port_get_buffer(j->outPort, frames);
    memset(buffer, 0, sizeof(sample_t) * frames);
    jack_ringbuffer_read(j->rb, (char *) buffer, sizeof(sample_t) * frames);

    return 0;
}


void JackOutput::click() {
    if (mCount == currentMeasure) mCount = 0;
    if (mCount == 0)
        jack_ringbuffer_write(rb, (char *) waveBar, waveLength * sizeof(sample_t));
    else jack_ringbuffer_write(rb, (char *) waveBeat, waveLength * sizeof(sample_t));
    mCount++;
}


float JackOutput::getAmp() {
    return MAX_AMP;
}


void JackOutput::setAmp(float newAmp) {
    memcpy(waveBar, waveExBar, waveLength * sizeof(sample_t));
    memcpy(waveBeat, waveExBeat, waveLength * sizeof(sample_t));

    for (int i = 0; i < (int) waveLength; i++) {
        waveBar[i] = waveBar[i] * newAmp;
        waveBeat[i] = waveBeat[i] * newAmp;
    }

    MAX_AMP = newAmp;
}
