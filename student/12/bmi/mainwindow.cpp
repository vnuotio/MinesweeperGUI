#include "mainwindow.hh"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countButton_clicked()
{
    string weight = ui->weightLineEdit->text().toStdString();
    string height = ui->heightLineEdit->text().toStdString();

    if (height == "" or height == "0")
    {
        update_info("Cannot count", "");
    }
    else
    {
        QString res_text;

        double w = stod(weight);
        double h = stod(height) / 100;

        double bmi = w / pow(h, 2);

        QString bmi_str = QString::number(bmi);

        if (bmi < 18.5)
        {
            res_text = "You are underweight.";
        }
        else if (bmi > 25)
        {
            res_text = "You are overweight.";
        }
        else
        {
            res_text = "Your weight is normal.";
        }

        update_info(bmi_str, res_text);
    }
}

void MainWindow::update_info(const QString& bmi, const QString& info)
{
    ui->infoTextBrowser->clear();

    ui->resultLabel->setText(bmi);
    ui->infoTextBrowser->insertPlainText(info);
}
