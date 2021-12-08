#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));

    ui->setupUi(this);

    ui->lcdNumberMin->setStyleSheet("""QLCDNumber { background-color: blue; color: white; }""");

    ui->lcdNumberSec->setStyleSheet("""QLCDNumber { background-color: green; color: white; }""");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_timer()
{
    if (sec == 59)
    {
        sec = 0;
        min++;
    }
    else
    {
        sec++;
    }
    update_lcd();
}

void MainWindow::update_lcd()
{
    ui->lcdNumberMin->display(min);
    ui->lcdNumberSec->display(sec);
}

void MainWindow::on_startButton_clicked()
{
    timer->start(1000);
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_resetButton_clicked()
{
    sec = 0;
    min = 0;
    update_lcd();
}
