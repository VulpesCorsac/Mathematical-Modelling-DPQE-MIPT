#include "Ant.h"
#include "AntStatus.h"
#include <QTcpSocket>

CAnt::CAnt()
:   m_AntName("Anonomous")
,   m_AntType(AtUnknown)
,   m_AntViewRadius(1)
,   m_AntStatus(AsUnknown)
,   m_AntLoad(AlEmpty)
,   m_AntPosX(0)
,   m_AntPosY(0)
,   m_AntGoalX(0)
,   m_AntGoalY(0)
,   m_AntLastGoalX(0)
,   m_AntLastGoalY(0)
,   m_LastStepNumber(0)
,   m_FoodResult(0)
,   m_StickResult(0)
,   m_GoalReachable(false)
,   m_MoveCommand(MdUnknown)
{
}

const char *g_AntLoads[AlCount] =
{
    "воздух"
,   "еду"
,   "веточку"
,   "воду"
,   "детку"

};

const char *CAnt::GetAntLoadString() const
{

    if(m_AntLoad < 0 || m_AntLoad >= AlCount)
    {
        return "что-то странное";
    }

    return g_AntLoads[m_AntLoad];
}

void CAnt::AddOpenedCell(const int index) // index = y * LabyrinthSizeX + x
{
    m_OpenedCells.insert(index);
}

size_t CAnt::GetCountOfOpenedCells() const
{
    return m_OpenedCells.size();
}

const std::string &CAnt::GetAntName() const
{
    return m_AntName;
}

void CAnt::SetAntName(const std::string &n)
{
        m_AntName = n;
}

AntType CAnt::GetAntType() const
{
    return m_AntType;
}

void CAnt::SetAntType(AntType s)
{
    m_AntType = s;
}

AntLoad CAnt::GetAntLoad() const
{
    return m_AntLoad;
}

void CAnt::SetAntLoad(const AntLoad l)
{
    m_AntLoad = l;
}

size_t CAnt::GetAntViewRadius() const
{
    return m_AntViewRadius;
}

size_t CAnt::GetAntViewSize() const
{
    return (m_AntViewRadius * 2) + 1;
}

void CAnt::SetAntViewRadius(const size_t r)
{
    m_AntViewRadius = r;
}

const std::string &CAnt::GetVisibleCells() const
{
    return m_VisibleCells;
}

void CAnt::SetVisibleCells(const std::string &n)
{
    m_VisibleCells = n;
}

const std::string &CAnt::GetVisibleDynCells() const
{
    return m_VisibleDynCells;
}

void CAnt::SetVisibleDynCells(const std::string &n)
{
    m_VisibleDynCells = n;
}

AntStatus CAnt::GetAntStatus() const
{
    return m_AntStatus;
}

void CAnt::SetAntStatus(const AntStatus s)
{
    m_AntStatus = s;
}

int CAnt::GetAntPosX() const
{
    return m_AntPosX;
}

void CAnt::SetAntPosX(const int x)
{
    m_AntPosX = x;
}

int CAnt::GetAntPosY() const
{
    return m_AntPosY;
}

void CAnt::SetAntPosY(const int y)
{
    m_AntPosY = y;
}

int CAnt::GetAntGoalX() const
{
    return m_AntGoalX;
}

void CAnt::SetAntGoalX(const int x)
{
    m_AntGoalX = x;
}

int CAnt::GetAntGoalY() const
{
    return m_AntGoalY;
}

void CAnt::SetAntGoalY(const int y)
{
    m_AntGoalY = y;
}

int CAnt::GetAntLastGoalX() const
{
    return m_AntGoalX;
}

void CAnt::SetAntLastGoalX(const int x)
{
    m_AntGoalX = x;
}

int CAnt::GetAntLastGoalY() const
{
    return m_AntGoalY;
}

void CAnt::SetAntLastGoalY(const int y)
{
    m_AntGoalY = y;
}

int CAnt::GetLastStepNumber() const
{
    return m_LastStepNumber;
}

void CAnt::SetLastStepNumber(const int s)
{
    m_LastStepNumber = s;
}

int CAnt::GetFoodResult() const
{
    return m_FoodResult;
}

void CAnt::SetFoodResult(const int r)
{
    m_FoodResult = r;
}

int CAnt::GetStickResult() const
{
    return m_StickResult;
}

void CAnt::SetStickResult(const int s)
{
    m_StickResult = s;
}

bool CAnt::GetGoalReachable() const
{
   return m_GoalReachable;
}

void CAnt::SetGoalReachable(const bool g)
{
    m_GoalReachable = g;
}

MoveDirection CAnt::GetAntMoveCommand() const
{
    return m_MoveCommand;
}

void CAnt::SetAntMoveCommand(const MoveDirection md)
{
    m_MoveCommand = md;
}

bool CAnt::AntIsBanned() const
{
    if (m_AntStatus == AsBanned)
    {
        return true;
    }
    return false;
}

bool CAnt::AntIsWinner() const
{
    if (m_AntStatus == AsWinner)
    {
        return true;
    }
    return false;
}

void CAnt::BanAnt()
{
    m_AntStatus = AsBanned;
    m_AntSocket->close();
}

QTcpSocket *CAnt::GetAntSocket() const
{
    return m_AntSocket;
}

void CAnt::SetAntSocket(QTcpSocket *socket)
{
    m_AntSocket = socket;
}


