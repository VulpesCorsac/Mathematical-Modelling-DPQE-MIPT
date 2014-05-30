#ifndef CANTLOOP_H
#define CANTLOOP_H

#include "Map.h"
#include "DynMap.h"
#include "Board.h"
#include <QtCore>

class CState;
class CStateParser;
class CItemParser;
class QTcpSocket;
class QString;

class CAntLoop
{
private:

    CMap m_Map;
    CDynMap m_DynMap;
    CBoard m_Board;

public:

    CAntLoop();

    void InitAnt(const std::string &name, const AntType type);

    void ConnectMap(const QString &ip, int port);

    void AntLoop();

    void DisconnectMap();

 private:

    void ApplyState(CAnt &ant, const CState &s);
    void ShowState(CAnt &ant);
    void UpdateAnt(CAnt &ant);
    bool ReadBlockFromStream(QTcpSocket* socket, CItemParser *itemParser);
    bool ReadBlockFromStream(std::istream &s, CItemParser *itemParser);
};

#endif // CANTLOOP_H
