#include "eventlistener.h"

EventListener::EventListener(QObject *parent) :
    QObject(parent) {}


bool EventListener::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *ev = (QMouseEvent *) event;
        if (ev->button() == Qt::RightButton) emit rightClicked(ev->x(), ev->y());
        else emit buttonClicked(obj->objectName());
    }
    if (event->type() == QEvent::Enter) emit buttonHover(obj->objectName());
    if (event->type() == QEvent::Leave) emit buttonLeave(obj->objectName());


    return QObject::eventFilter(obj, event);
}
