#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("1942");
    a.setOrganizationName("jsfdez");
    GameWindow w;
    w.show();

    return a.exec();
}
