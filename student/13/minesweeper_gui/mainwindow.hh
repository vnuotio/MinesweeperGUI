/* Handles the GUI side of this minesweeper game.
 * Vector of ButtonStructs contains all buttons and their coordinates.
 * Constructor creates a new GameBoard instance, which is deleted
 * either at reset or program exit.
 *
 * TO PLAY:
 * -Insert a seed as a number or leave blank for random seed
 * -Press start
 * -Left-click on a tile to open it, right click to place/remove flag
 * Game ends when a mine is hit, or all mines have been flagged.
 * The program can be closed with the "Close"-button
 * The game can be reset with the "Reset"-button.
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <vector>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QtGui>

struct ButtonStruct
{
    QPushButton* button;
    Square* square;
    int x;
    int y;
};

using ButtonVector = std::vector<ButtonStruct>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    QString gameLostMsg = "Boom! Game over!";
    QString gameWonMsg = "You won! Congrats!";

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSquareLeftClick();

    void onSquareRightClick();

    void on_startButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    ButtonVector buttons_;
    GameBoard* gameBoard_;

    // Gets the seed from the corresponding lineEdit.
    // Returns either the given seed as int or if none is given,
    // returns number generated from system time.
    int readSeed();

    // Creates buttons ButtonStructs and adds the latter into
    // <buttons_> when called.
    void initBoardGUI();

    // Opens a given tile, displaying the adjacent count or "M" if
    // there was a mine.
    void openButton(ButtonStruct& bs);

    // Adds an "F" flag to an unopened tile or removes it.
    void flag(ButtonStruct& bs);

    // Goes over all the tiles in <buttons_> and labels the opened
    // tiles with the count of adjacent mines.
    void refreshBoard();

    // Called when the player hits a mine or wins. Locks the tiles so the game
    // appears frozen. Exit or reset-start to unlock.
    void gameOver(QString msg);
};
#endif // MAINWINDOW_HH
