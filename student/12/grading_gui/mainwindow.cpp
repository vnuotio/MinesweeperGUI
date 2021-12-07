#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(MAX_N_POINTS);

    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);

    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);

    ui->spinBoxE->setMinimum(0);
    ui->spinBoxE->setMaximum(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxN_valueChanged()
{
    n = ui->spinBoxN->value();
}

void MainWindow::on_spinBoxG_valueChanged()
{
    g = ui->spinBoxG->value();
}

void MainWindow::on_spinBoxP_valueChanged()
{
    p = ui->spinBoxP->value();
}

void MainWindow::on_spinBoxE_valueChanged()
{
    e = ui->spinBoxE->value();
}


void MainWindow::on_countPushButton_clicked()
{
    unsigned int res = count_final_grade(n, g, p, e);
    QString resText = QString::number(res);

    ui->textBrowser->clear();
    ui->textBrowser->insertPlainText("Total grade: ");
    ui->textBrowser->insertPlainText(resText);
}

