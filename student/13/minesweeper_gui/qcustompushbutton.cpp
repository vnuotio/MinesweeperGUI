#include "qcustompushbutton.hh"

QCustomPushButton::QCustomPushButton( QString s, QWidget *parent) :
    QPushButton(parent)
{
    this->setText(s);
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
