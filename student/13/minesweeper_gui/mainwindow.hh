#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QtGui>

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
    void buttonClickHandler();

private:
    Ui::MainWindow *ui;
    int seed_;
    void askSeed();
    void initBoard();
};
#endif // MAINWINDOW_HH
