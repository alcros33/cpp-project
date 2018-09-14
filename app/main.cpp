#include "qtexample.h"
#include <QApplication>
#include "Config.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTExample w;
    w.show();

    return app.exec();
}

