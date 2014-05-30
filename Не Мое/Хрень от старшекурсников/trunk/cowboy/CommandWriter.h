#ifndef CCOMMANDWRITER_H
#define CCOMMANDWRITER_H

class QTcpSocket;
class CBoard;
#include "Ant.h"


class CCommandWriter
{
private:
    QTcpSocket *m_Socket;
    std::string m_Command;

public:
    CCommandWriter(QTcpSocket *socket);

    bool SendFirstCommand(const CAnt &ant);

    bool SendCommand(const CAnt &ant, const CBoard &b);
};

#endif // CCOMMANDWRITER_H
