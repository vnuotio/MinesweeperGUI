#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "qcustompushbutton.hh"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameBoard_(new GameBoard)
    , timer_(new QTimer)
{
    ui->setupUi(this);
    connect(timer_, &QTimer::timeout, this, &MainWindow::updateTimer);
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
            QPushButton* newButton = new QCustomPushButton(this);
            Square* thisSquare = gameBoard_->getSquare(i, j);
            ButtonStruct newButtonStruct = {newButton, thisSquare, i, j};

            setTileImage(newButtonStruct, "unknown.png");

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
        setTileImage(bs, "mine.png");
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
        setTileImage(bs, "flag.png");
        bs.square->addFlag();
    }
    // Remove flag
    else
    {
        setTileImage(bs, "unknown.png");
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
            b.button->setIcon(QIcon());

            b.button->setDisabled(true);

            int count = b.square->countAdjacent();
            QString s = QString::number(count);
            b.button->setText(s);
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
    timer_->stop();
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

    ui->timerLabel->setText("0:00");
    timer_->start(1000);
}

void MainWindow::on_resetButton_clicked()
{
    delete gameBoard_;
    buttons_.clear();

    timer_->stop();
    timerSec_ = 0;
    timerMin_ = 0;

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

void MainWindow::updateTimer()
{
    if (timerSec_ == 59)
    {
        timerSec_ = 0;
        timerMin_++;
    }
    else
    {
        timerSec_++;
    }

    std::string secPad = (timerSec_ < 10)? "0" : "";

    std::string time = std::to_string(timerMin_) + ":" + secPad + std::to_string(timerSec_);
    ui->timerLabel->setText(QString::fromStdString(time));
}

void MainWindow::setTileImage(ButtonStruct &bs, QString img)
{
    bs.button->setText("");
    QString path = ":/Resources/" + img;
    QPixmap image(path);
    image = image.scaled(BUTTON_SIDE_SIZE, BUTTON_SIDE_SIZE);
    bs.button->setIcon(image);
}
