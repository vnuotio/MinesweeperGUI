#ifndef QRIGHTCLICKBUTTON_HH
#define QRIGHTCLICKBUTTON_HH

#include <QPushButton>
#include <QMouseEvent>

class QRightClickButton : public QPushButton
{
    Q_OBJECT;
public:
     explicit QRightClickButton(QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightClicked();
};

#endif // QRIGHTCLICKBUTTON_HH
