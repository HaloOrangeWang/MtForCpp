#include "total.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    wstore = new StoreWindow();

    w.GameStart();
    w.show();

    return a.exec();
}
