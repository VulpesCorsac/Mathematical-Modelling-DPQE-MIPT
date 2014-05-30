#ifndef CSTATEWRITER_H
#define CSTATEWRITER_H

#include <iostream>
#include <fstream>
#include "Map.h"
#include "Board.h"

class CStateWriter
{
private:
    QTcpSocket *m_AntSocket;
    std::string m_State;

public:
    CStateWriter(QTcpSocket *socket);

    bool SendState(int antNumber, CMap &map, CBoard &board);

};

#endif // CSTATEWRITER_H
