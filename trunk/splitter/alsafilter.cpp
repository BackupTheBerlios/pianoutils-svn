#include "alsafilter.h"
#include <stdio.h>

AlsaFilter::AlsaFilter(QObject *parent) : QThread(parent), currentNote(36),
    ch1Num(0), ch2Num(1), ch1Shift(0), ch2Shift(0) {
    int client;

    snd_seq_open(&seq, "default", SND_SEQ_OPEN_DUPLEX, 0);
    snd_seq_set_client_name(seq, "splitter");
    client = snd_seq_client_id(seq);

    inport = snd_seq_create_simple_port(seq, "in",
        SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, SND_SEQ_PORT_TYPE_APPLICATION);

    outport = snd_seq_create_simple_port(seq, "out",
        SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, SND_SEQ_PORT_TYPE_APPLICATION);
}


void AlsaFilter::run() {
    snd_seq_event_t *event;

    while(snd_seq_event_input(seq, &event) >= 0) {
        snd_seq_ev_set_direct(event);
        snd_seq_ev_set_subs(event);

        if (event->type == SND_SEQ_EVENT_NOTEON || event->type == SND_SEQ_EVENT_NOTEOFF) {
            if (event->data.note.note >= currentNote) {
                event->data.note.channel = ch2Num;
                event->data.note.note += ch2Shift;
            }
            else {
                event->data.note.channel = ch1Num;
                event->data.note.note += ch1Shift;
            }
        }

        snd_seq_ev_set_source(event, outport);
        snd_seq_event_output_direct(seq, event);
        snd_seq_free_event(event);
    }
}


void AlsaFilter::setNote(int i) {
    currentNote = i;
}


void AlsaFilter::setChNum1(int num) {
    ch1Num = num;
}


void AlsaFilter::setChNum2(int num) {
    ch2Num = num;
}


void AlsaFilter::setChShift1(int notes) {
    ch1Shift = notes;
}


void AlsaFilter::setChShift2(int notes) {
    ch2Shift = notes;
}
