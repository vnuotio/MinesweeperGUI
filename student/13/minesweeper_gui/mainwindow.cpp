#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <algorithm>

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

void MainWindow::squareClickHandler()
{
    for (auto& b : buttons_)
    {
        if (b.button == sender())
        {
            openButton(b);
            return;
        }
    }
}

void MainWindow::initBoardGUI()
{
    QGridLayout* grid = ui->gridLayout;

    // Remove spacing so the tiles pack closely.
    grid->setSpacing(0);

    // Vertical spacers
    /*grid->addItem(new QSpacerItem(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE,
                                  QSizePolicy::Minimum, QSizePolicy::Expanding),
                  0, 0, 1, BOARD_SIDE + 2);*/

    grid->addItem(new QSpacerItem(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE,
                                  QSizePolicy::Minimum, QSizePolicy::Expanding),
                  BOARD_SIDE + 1, 0, 1, BOARD_SIDE + 2);

    // Horizontal spacers
    /*grid->addItem(new QSpacerItem(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE,
                                  QSizePolicy::Expanding, QSizePolicy::Minimum),
                  1, 0, BOARD_SIDE, 1);*/

    grid->addItem(new QSpacerItem(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE,
                                  QSizePolicy::Expanding, QSizePolicy::Minimum),
                  1, BOARD_SIDE + 1, BOARD_SIDE, 1);

    for (int i = 1; i < BOARD_SIDE + 1; i++)
    {
        for (int j = 1; j < BOARD_SIDE + 1; j++)
        {
            QPushButton* newButton = new QPushButton("?", this);
            ButtonStruct newButtonStruct = {newButton, i - 1, j - 1};
            buttons_.push_back(newButtonStruct);

            connect(newButton, &QPushButton::clicked, this, &MainWindow::squareClickHandler);
            newButton->setFixedHeight(BUTTON_SIDE_SIZE);
            newButton->setFixedWidth(BUTTON_SIDE_SIZE);
            grid->addWidget(newButton, i, j);
        }
    }
}

void MainWindow::openButton(ButtonStruct& bs)
{
    if (not gameBoard_.openSquare(bs.x, bs.y))
    {
        bs.button->setText("M");
    }
    else
    {
        bs.button->setText("E");
    }
}

void MainWindow::on_startButton_clicked()
{
    int seed = readSeed();

    ui->startButton->hide();

    gameBoard_.init(seed);
    initBoardGUI();
}

void MainWindow::on_resetButton_clicked()
{
}

int MainWindow::readSeed()
{
    QString seedString = ui->seedLineEdit->text();
    if (seedString == "")
    {
        ui->seedInfoLabel->setText("Using system generated number as seed");
        return time(NULL);
    }
    else
    {
        QString seedInfoText = "Using seed " + seedString;
        ui->seedInfoLabel->setText(seedInfoText);
        return seedString.toInt();
    }
}
