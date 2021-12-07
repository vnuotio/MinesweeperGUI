#include "mainwindow.hh"

#include <QApplication>

bool case_insensitive_compare(const string& a, const string& b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (size_t i = 0; i < a.size(); i++)
    {
        char ai = a.at(i);
        char bi = b.at(i);

        if (toupper(ai) != toupper(bi))
        {
            return false;
        }
    }
    return true;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
