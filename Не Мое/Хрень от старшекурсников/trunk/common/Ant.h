#ifndef ANT_H
#define ANT_H

#include "AntType.h"
#include "AntStatus.h"
#include "MoveDirection.h"
#include <string>
#include <set>

class QTcpSocket;

enum AntLoad // что может нести муравей
{
    AlError = -1
,   AlEmpty = 0
,   AlFood
,   AlStick
,   AlWater
,   AlChild

,   AlCount

};

class CAnt
{

private:

    std::string m_AntName;
    AntType m_AntType;
    size_t m_AntViewRadius;
    std::string m_VisibleCells;
    std::string m_VisibleDynCells;
    AntStatus m_AntStatus;
    AntLoad m_AntLoad;
    int m_AntPosX;
    int m_AntPosY;
    int m_AntGoalX;
    int m_AntGoalY;
    int m_AntLastGoalX;
    int m_AntLastGoalY;
    int m_LastStepNumber;
    int m_FoodResult;
    int m_StickResult;
    bool m_GoalReachable;

    MoveDirection m_MoveCommand;
    QTcpSocket *m_AntSocket;

    std::set<int> m_OpenedCells;

public:

    CAnt();

    void AddOpenedCell(const int index); // index = y * LabyrinthSizeX + x

    size_t GetCountOfOpenedCells() const;

    const std::string &GetAntName() const;

    void SetAntName(const std::string &n);

    AntType GetAntType() const;

    void SetAntType(AntType s);

    size_t GetAntViewRadius() const;

    void SetAntViewRadius(const size_t r);

    size_t GetAntViewSize() const;

    const std::string &GetVisibleCells() const;

    void SetVisibleCells(const std::string &n);

    const std::string &GetVisibleDynCells() const;

    void SetVisibleDynCells(const std::string &n);

    AntStatus GetAntStatus() const;

    void SetAntStatus(const AntStatus s);

    AntLoad GetAntLoad() const;

    const char *GetAntLoadString() const;

    void SetAntLoad(const AntLoad l);

    int GetAntPosX() const;

    void SetAntPosX(const int x);

    int GetAntPosY() const;

    void SetAntPosY(const int y);

    int GetAntGoalX() const;

    void SetAntGoalX(const int x);

    int GetAntGoalY() const;

    void SetAntGoalY(const int y);

    int GetAntLastGoalX() const;

    void SetAntLastGoalX(const int x);

    int GetAntLastGoalY() const;

    void SetAntLastGoalY(const int y);

    int GetLastStepNumber() const;

    void SetLastStepNumber(const int s);

    int GetFoodResult() const;

    void SetFoodResult(const int r);

    int GetStickResult() const;

    void SetStickResult(const int s);

    bool GetGoalReachable() const;

    void SetGoalReachable(const bool g);

    MoveDirection GetAntMoveCommand() const;

    void SetAntMoveCommand(const MoveDirection md);

    bool AntIsBanned() const;

    bool AntIsWinner() const;

    void BanAnt();

    QTcpSocket *GetAntSocket() const;

    void SetAntSocket(QTcpSocket *socket);

};

#endif // ANT_H
