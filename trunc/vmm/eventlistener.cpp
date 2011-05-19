#include "eventlistener.h"
#include <stdio.h>

EventListener::EventListener(QObject *parent) :
    QObject(parent) {}


bool EventListener::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) emit buttonClicked(obj->objectName());
    if (event->type() == QEvent::Enter) emit buttonHover(obj->objectName());
    if (event->type() == QEvent::Leave) emit buttonLeave(obj->objectName());
    if (event->type() == QEvent::MouseButtonPress) emit buttonClk(obj->objectName());

    return QObject::eventFilter(obj, event);
}
