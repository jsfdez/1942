#include <QApplication>

#include "gamewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("1942");
    a.setOrganizationName("jsfdez");
    GameWindow w;
    w.show();

    return a.exec();
}
