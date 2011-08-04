#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>

class EventListener : public QObject
{
    Q_OBJECT
public:
    explicit EventListener(QObject *parent = 0);

signals:
    void buttonClicked(QString b);
    void buttonHover(QString b);
    void buttonLeave(QString b);
    void rightClicked(int x, int y);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // EVENTLISTENER_H
