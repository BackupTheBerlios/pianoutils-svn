#include "customlcd.h"

CustomLCD::CustomLCD(QWidget *parent) : QLCDNumber(parent) {}

void CustomLCD::mousePressEvent(QMouseEvent *ev) {
    if (ev->button() == Qt::LeftButton) emit clicked();
    else QWidget::mousePressEvent(ev);
}
