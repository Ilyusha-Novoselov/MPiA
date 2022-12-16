#include "paint.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Paint w;
    w.setWindowTitle("RGZ");
    w.show();

    return a.exec();
}
