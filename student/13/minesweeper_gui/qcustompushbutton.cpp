#include "qcustompushbutton.hh"

QCustomPushButton::QCustomPushButton(QWidget *parent) :
    QPushButton(parent)
{
}

void QCustomPushButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        emit leftClicked();
    }
    else if (e->button() == Qt::RightButton)
    {
        emit rightClicked();
    }
}
