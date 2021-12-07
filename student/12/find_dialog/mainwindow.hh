#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <fstream>

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
    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;
    void setText(const QString& msg);
    bool findText(std::ifstream& file, std::string& searched);
};
#endif // MAINWINDOW_HH
