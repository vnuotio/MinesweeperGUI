#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <algorithm>
#include <QtDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setText(const QString& msg)
{
    ui->textBrowser->clear();
    ui->textBrowser->insertPlainText(msg);
}

string to_lowercase(string s)
{
    for (char& c : s)
    {
        c = tolower(c);
    }
    return s;
}

bool MainWindow::findText(ifstream& file, string& searched)
{
    string line = "";
    while (getline(file, line))
    {
        if (ui->matchCheckBox->isChecked())
        {
            if (line.find(searched) != string::npos)
            {
                return true;
            }
        }
        else
        {
            string line_lower = to_lowercase(line);
            string searched_lower = to_lowercase(searched);

            if (line_lower.find(searched_lower) != string::npos)
            {
                return true;
            }
        }
    }
    return false;
}


void MainWindow::on_findPushButton_clicked()
{
    string searched = ui->keyLineEdit->text().toStdString();
    string file_name = ui->fileLineEdit->text().toStdString();
    ifstream file(file_name);

    if (not file)
    {
        setText("File not found");
    }
    else if (searched == "")
    {
        setText("File found");
    }
    else if (findText(file, searched))
    {
        setText("Word found");
    }
    else
    {
        setText("Word not found");
    }
    file.close();
}

