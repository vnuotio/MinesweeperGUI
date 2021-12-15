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
    int x;
    int y;
};

using ButtonVector = std::vector<ButtonStruct>;

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
    void squareClickHandler();

    void on_startButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    ButtonVector buttons_;
    GameBoard gameBoard_;

    int readSeed();
    void initBoardGUI();
    void openButton(ButtonStruct&);
};
#endif // MAINWINDOW_HH
