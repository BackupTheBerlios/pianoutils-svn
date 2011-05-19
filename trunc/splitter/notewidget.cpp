#include "notewidget.h"

NoteWidget::NoteWidget(QWidget *parent) : QSpinBox(parent) {
    setMinimum(0);
    setMaximum(0x7F);
}

QString NoteWidget::textFromValue(int value) const {
    QString arr[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    int note = value % 12;
    return QString("%1%2").arg(arr[note]).arg(value / 12 - 2);
}
