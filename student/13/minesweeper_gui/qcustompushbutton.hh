/* Extends the QPushButton class.
 * Adds signals for right- and left-clicking.
 */
#ifndef QCUSTOMPUSHBUTTON_HH
#define QCUSTOMPUSHBUTTON_HH

#include <QPushButton>
#include <QMouseEvent>

class QCustomPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QCustomPushButton(QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void leftClicked();
    void rightClicked();

public slots:
};

#endif // QCUSTOMPUSHBUTTON_HH
