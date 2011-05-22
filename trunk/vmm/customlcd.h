#ifndef CUSTOMLCD_H
#define CUSTOMLCD_H

#include <QtGui/QLCDNumber>

class CustomLCD : public QLCDNumber
{
Q_OBJECT
public:
    CustomLCD(QWidget *parent = 0);

signals:
    void clicked();

private:
    void mousePressEvent(QMouseEvent *);
};

#endif // CUSTOMLCD_H
