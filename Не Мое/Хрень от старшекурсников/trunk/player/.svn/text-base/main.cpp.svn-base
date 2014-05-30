
#include <QApplication>
#include "PlayerLoop.h"
#include <QtGui>
#include <QObject>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene(QRectF(0, 0, 1600, 1500));

    const int defaultDelay = 100;

    CPlayerLoop  player(&scene);

    player.InitPlayer(defaultDelay);    

    return app.exec();
}
