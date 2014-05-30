#include "GameLoop.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const int defaultPort = 31415;
    const int defaultNumberOfAnts = 1;
    const int defaultDelay = 150;

    int numberOfAnts = defaultNumberOfAnts;

    if (QCoreApplication::arguments().size() > 1)
    {
        bool ok = false;
        int tempValue = QCoreApplication::arguments().at(1).toInt(&ok, 10);
        if (ok)
        {
            numberOfAnts = tempValue;
        }
    }

    CGameLoop game;

    game.ReadMap();

    game.GameLoop(defaultPort, numberOfAnts, defaultDelay);

    game.CloseGame();

    return 0;
}




