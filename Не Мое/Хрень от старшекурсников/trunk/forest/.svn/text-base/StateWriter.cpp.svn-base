#include "StateWriter.h"
#include <QTcpSocket>
#include <sstream>

CStateWriter::CStateWriter(QTcpSocket *socket)
:   m_AntSocket(socket)
,   m_State("No_State\n\n")
{
}

static bool WriteStateToSocket(const std::string &state, QTcpSocket *socket)
{
    for (size_t i = 0; i < state.length(); i++)
    {
        if(!socket->putChar(state.at(i)))
        {
            return false;
        }
    }

    socket->waitForBytesWritten(-1);
    return true;
}


bool CStateWriter::SendState(int antNumber, CMap &map, CBoard &board)
{
    std::stringstream sstream;
    const CAnt &a = map.GetAnt(antNumber);

    sstream << "Ant_Pos_X " << a.GetAntPosX() << "\n" <<
               "Ant_Pos_Y " << a.GetAntPosY() << "\n" <<
               "Ant_Status " << a.GetAntStatus() << "\n" <<
               "Map_Size " << map.GetMapSizeX() << "\n" <<
               "View_Radius " << a.GetAntViewRadius() << "\n" <<
               "View_Cells " << a.GetVisibleCells() << "\n" <<
               "View_Dyn_Cells " << a.GetVisibleDynCells() << "\n" <<
               "Number_Of_Messages " << BkCount << "\n";

    for(int numberMessageBoard = 0; numberMessageBoard < BkCount; numberMessageBoard++)
     {

         BoardKey bk = (BoardKey)numberMessageBoard;
         if(!(board.GetMessage(bk).empty()))
         {
             sstream << BoardKeyToString(bk) << " ";
             std::vector<int> messageBoard = board.GetMessage(bk);
             for(size_t number = 0; number <  messageBoard.size(); ++number)
             {
                 sstream << messageBoard[number] << " ";
             }
         sstream << "\n";
         }
     }
     sstream << "\n";

     //  << "Please Enter Command:\n"; // временно. Исключительно для игр с telnet

    m_State = sstream.str();

    //std::cout << m_State << std::endl << std::flush;

    return WriteStateToSocket(m_State, m_AntSocket);
}





