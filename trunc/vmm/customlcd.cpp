#include "customlcd.h"

CustomLCD::CustomLCD(QWidget *parent) : QLCDNumber(parent) {}

void CustomLCD::mousePressEvent(QMouseEvent *ev) {
    emit clicked();
}
