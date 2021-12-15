#ifndef QCUSTOMPUSHBUTTON_HH
#define QCUSTOMPUSHBUTTON_HH

#include <QPushButton>
#include <QMouseEvent>

class QCustomPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QCustomPushButton(QString s, QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void leftClicked();
    void rightClicked();

public slots:
};

#endif // QCUSTOMPUSHBUTTON_HH
