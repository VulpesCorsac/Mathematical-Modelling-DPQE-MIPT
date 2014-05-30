#include "CommandWriter.h"
#include "Board.h"
#include "Boardkey.h"
#include <QTcpSocket>
#include <sstream>

CCommandWriter::CCommandWriter(QTcpSocket *socket)
:   m_Socket(socket)
,   m_Command("No_Command\n\n")
{
}

static bool WriteCommandToSocket(const std::string &command, QTcpSocket *socket)
{
    for (size_t i = 0; i < command.length(); i++)
    {
        if(!socket->putChar(command.at(i)))
        {
            return false;
        }
    }

    socket->waitForBytesWritten(-1);
    return true;
}

bool CCommandWriter::SendFirstCommand(const CAnt &ant)
{
    std::stringstream sstream;

    sstream << "Ant_Name " << ant.GetAntName() << "\n" <<
               "Ant_Type " << AntTypeToString(ant.GetAntType()) << "\n\n";


    m_Command = sstream.str();

    return WriteCommandToSocket(m_Command, m_Socket);
}

bool CCommandWriter::SendCommand(const CAnt &ant, const CBoard &b)
{
    std::stringstream sstream;

    sstream << "Command_Move " << MoveDirectionToString(ant.GetAntMoveCommand()) << "\n"
            << "Number_Of_Messages 0" << "\n";
    for(int numberMessageBoard = 0; numberMessageBoard < BkCount; numberMessageBoard++)
     {

         BoardKey bk = (BoardKey)numberMessageBoard;

         if(!(b.GetMessage(bk).empty()))
         {
             sstream << BoardKeyToString(bk) << " ";
             std::vector<int> messageBoard = b.GetMessage(bk);
             for(size_t number = 0; number <  messageBoard.size(); ++number)
             {
                 sstream << messageBoard[number] << " ";
             }
         sstream << "\n";
         }
     }

    sstream << "\n";
    m_Command = sstream.str();

    return WriteCommandToSocket(m_Command, m_Socket);
}
