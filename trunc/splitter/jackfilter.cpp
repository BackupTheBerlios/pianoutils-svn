#include "jackfilter.h"
#include <stdio.h>

int process(jack_nframes_t nframes, void *arg) {
    int j;
    data *par = (data *) arg;

    jack_midi_event_t *event = (jack_midi_event_t *) jack_port_get_buffer(par->inPort, nframes);
    int eCount = jack_midi_get_event_count(event);
    void *buffer = jack_port_get_buffer(par->outPort, nframes);
    jack_midi_clear_buffer(buffer);

    for (eCount, j = 0; eCount > 0; eCount--, j++) {
        jack_midi_event_t nextE;
        jack_midi_event_get(&nextE, event, j);

        // Filtering by channel
        char ch = nextE.buffer[0] & 0x0F;

        if (par->channelFilter >= 0) {
            if (ch != par->channelFilter) return 0;
        }

        if (nextE.buffer[0] & 0x80 || nextE.buffer[0] & 0x90) {
            if (nextE.buffer[1] >= par->currentNote) {
                nextE.buffer[0] &= 0xF0;
                nextE.buffer[0] += par->ch2Num;
                nextE.buffer[1] += par->ch2Shift;
            }
            else {
                nextE.buffer[0] &= 0xF0;
                nextE.buffer[0] += par->ch1Num;
                nextE.buffer[1] += par->ch1Shift;
            }

        }


        jack_midi_event_write(buffer, nextE.time, nextE.buffer, nextE.size);
    }

    return 0;
}


JackFilter::JackFilter(QObject *parent) : QObject(parent) {
    par.channelFilter = -1;
    par.currentNote = 36;
    par.ch1Num = 0;
    par.ch2Num = 1;
    par.ch1Shift = 0;
    par.ch2Shift = 0;

    // Try to init client
    if ((client = jack_client_open("splitter", JackNoStartServer, NULL)) == 0) {
        throw -1;
        return;
    }

    par.inPort = jack_port_register(client, "in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
    par.outPort = jack_port_register(client, "out", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

    jack_set_process_callback(client, process, &par);

    if (jack_activate(client)) throw -1;
}


JackFilter::~JackFilter() {
    if (client != NULL) jack_client_close(client);
}


void JackFilter::setNote(int i) {
    par.currentNote = i;
}

void JackFilter::setChFilter(int chnl) {
    par.channelFilter = chnl - 1;
}


void JackFilter::setChNum1(int num) {
    par.ch1Num = num;
}


void JackFilter::setChNum2(int num) {
    par.ch2Num = num;
}


void JackFilter::setChShift1(int notes) {
    par.ch1Shift = notes;
}


void JackFilter::setChShift2(int notes) {
    par.ch2Shift = notes;
}
