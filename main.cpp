
#include <QApplication>
#include "solaropengl.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    SolarOpenGL w;
    w.resize(400, 300);
    w.show();


    return app.exec();
}
