#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QSpinBox>

class NoteWidget : public QSpinBox
{
    Q_OBJECT
public:
    explicit NoteWidget(QWidget *parent = 0);

protected:
    QString textFromValue(int val) const;

signals:

public slots:

};

#endif // NOTEWIDGET_H
