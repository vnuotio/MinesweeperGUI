#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "qcustompushbutton.hh"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameBoard_(new GameBoard)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete gameBoard_;
    delete ui;
}

void MainWindow::initBoardGUI()
{
    QGridLayout* grid = ui->gridLayout;

    // Remove spacing so the tiles pack closely.
    grid->setSpacing(0);

    // Vertical spacers
    grid->addItem(new QSpacerItem(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE,
                                  QSizePolicy::Minimum, QSizePolicy::Expanding),
                  0, 0, 1, BOARD_SIDE + 2);

    grid->addItem(new QSpacerItem(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE,
                                  QSizePolicy::Minimum, QSizePolicy::Expanding),
                  BOARD_SIDE + 1, 0, 1, BOARD_SIDE + 2);

    // Horizontal spacers
    grid->addItem(new QSpacerItem(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE,
                                  QSizePolicy::Expanding, QSizePolicy::Minimum),
                  1, 0, BOARD_SIDE, 1);

    grid->addItem(new QSpacerItem(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE,
                                  QSizePolicy::Expanding, QSizePolicy::Minimum),
                  1, BOARD_SIDE + 1, BOARD_SIDE, 1);

    for (int i = 0; i < BOARD_SIDE; i++)
    {
        for (int j = 0; j < BOARD_SIDE; j++)
        {
            QPushButton* newButton = new QCustomPushButton("?", this);
            Square* thisSquare = gameBoard_->getSquare(i, j);
            ButtonStruct newButtonStruct = {newButton, thisSquare, i, j};
            buttons_.push_back(newButtonStruct);

            connect(newButton, SIGNAL(leftClicked()), this,
                    SLOT(onSquareLeftClick()));

            connect(newButton, SIGNAL(rightClicked()), this,
                    SLOT(onSquareRightClick()));

            newButton->setFixedHeight(BUTTON_SIDE_SIZE);
            newButton->setFixedWidth(BUTTON_SIDE_SIZE);
            grid->addWidget(newButton, i + 1, j + 1);
        }
    }
}

void MainWindow::openButton(ButtonStruct& bs)
{
    bool hasMine = not gameBoard_->openSquare(bs.x, bs.y);
    refreshBoard();

    if (hasMine)
    {
        gameOver(gameLostMsg);
    }
    else if (gameBoard_->isGameOver())
    {
        gameOver(gameWonMsg);
    }
}

void MainWindow::flag(ButtonStruct &bs)
{
    // Add flag
    if (not bs.square->hasFlag())
    {
        bs.button->setText("F");
        bs.square->addFlag();
    }
    // Remove flag
    else
    {
        bs.button->setText("?");
        bs.square->removeFlag();
    }

    gameBoard_->setSquare(*bs.square, bs.x, bs.y);

    if (gameBoard_->isGameOver())
    {
        gameOver(gameWonMsg);
    }
}

void MainWindow::refreshBoard()
{
    for (auto& b : buttons_)
    {
        if (b.square->isOpen())
        {
            b.button->setDisabled(true);
            if (not b.square->hasMine())
            {
                int count = b.square->countAdjacent();
                QString s = QString::number(count);
                b.button->setText(s);
            }
            else
            {
                b.button->setText("M");
            }
        }
    }
}

void MainWindow::gameOver(QString msg)
{
    for (auto& b : buttons_)
    {
        b.button->setDisabled(true);
    }
    ui->gameInfoLabel->setText(msg);
}

void MainWindow::onSquareLeftClick()
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

void MainWindow::onSquareRightClick()
{
    for (auto& b : buttons_)
    {
        if (b.button == sender())
        {
            flag(b);
            return;
        }
    }
}

void MainWindow::on_startButton_clicked()
{
    int seed = readSeed();

    ui->startButton->hide();

    gameBoard_->init(seed);
    initBoardGUI();
}

void MainWindow::on_resetButton_clicked()
{
    delete gameBoard_;
    buttons_.clear();

    gameBoard_ = new GameBoard;
    ui->startButton->show();
}

int MainWindow::readSeed()
{
    QString seedString = ui->seedLineEdit->text();
    if (seedString == "")
    {
        ui->gameInfoLabel->setText("Using system generated number as seed");
        return time(NULL);
    }
    else
    {
        QString seedInfoText = "Using seed " + seedString;
        ui->gameInfoLabel->setText(seedInfoText);
        return seedString.toInt();
    }
}
