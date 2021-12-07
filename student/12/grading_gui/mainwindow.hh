#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "gradecounter.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBoxN_valueChanged();
    void on_spinBoxG_valueChanged();
    void on_spinBoxP_valueChanged();
    void on_spinBoxE_valueChanged();

    void on_countPushButton_clicked();

private:
    Ui::MainWindow *ui;
    unsigned int n = 0;
    unsigned int g = 0;
    unsigned int p = 0;
    unsigned int e = 0;
};
#endif // MAINWINDOW_HH
