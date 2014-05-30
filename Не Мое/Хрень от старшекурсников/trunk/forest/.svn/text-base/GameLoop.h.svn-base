#ifndef CGAMELOOP_H
#define CGAMELOOP_H

#include "Map.h"
#include "DynMap.h"
#include "Board.h"
#include <QtCore>

class CCommand;
class CFirstCommand;
class CCommandParser;
class CItemParser;
class QTcpSocket;

enum ManagerDirection
{
    GoFree = 0
,   ToStock
,   ToHill

};


class CGameLoop
{
private:

    CMap m_Map;
    CDynMap m_DynMap;
    CBoard m_Board;
    int m_GameStep;
    int m_FoodInHill;
    int m_FoodInStock;
    int m_StickInHill;
    int m_ChildrenGrownup;
    int m_CowInHill;
    int m_MushroomInHill;
    ManagerDirection m_ManagerDirection;

public:
    CGameLoop();

    void ReadMap();

    void GameLoop(int port, int ant, int delay);

    void CloseGame();


private:
    void SetAntCellsOpened(int antNumber);

    bool IsAntWinner(int antNumber);

    bool IsNeighbour(const CAnt &ant, const AntType neighbour);

    void ApplyFirstCommand(int antNumber, const CFirstCommand &firstCommand);

    void ApplyCommand(int antNumber, const CCommand &command);

    void PlaceAnt(int antNumber);

    void UpdateMap();

    void ShowMap();

    void UpdateDynMap();

    void UpdateBoard(const CCommand &command);

    int NumberOfPlayingAnts();

    bool ReadBlockFromStream(QTcpSocket* socket, CItemParser *itemParser);

    bool ReadBlockFromStream(std::istream &s, CItemParser *itemParser);

    void WriteLog(std::ofstream &log);
};

#endif // CGAMELOOP_H
