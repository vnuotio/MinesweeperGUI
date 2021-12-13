#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClickHandler()
{

}

void MainWindow::askSeed()
{

}

void MainWindow::initBoard()
{
    QWidget* central = new QWidget(this);
    QGridLayout* grid = new QGridLayout(central);

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
            QPushButton* button = new QPushButton("?", this);
            button->setFixedHeight(BUTTON_SIDE_SIZE);
            button->setFixedWidth(BUTTON_SIDE_SIZE);
            grid->addWidget(button, i, j);
        }
    }

    setCentralWidget(central);
}
