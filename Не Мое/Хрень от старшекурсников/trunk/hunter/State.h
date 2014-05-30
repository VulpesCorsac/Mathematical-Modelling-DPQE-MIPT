#ifndef CSTATE_H
#define CSTATE_H

#include <string>
#include <vector>
#include "AntStatus.h"
#include "Boardkey.h"

class CState
{
private:

    int m_AntPosX; // текущие координаты муравья
    int m_AntPosY;
    AntStatus m_AntStatus;
    int m_MapSize;
    int m_ViewRadius;
    std::string m_VisibleMap;
    std::string m_VisibleDynMap;
    int m_NumberOfMessages;
    std::vector<int> m_Messages[BkCount];

public:

    CState();

    void SetPosX(const int x);

    int GetPosX() const;

    void SetPosY(const int y);

    int GetPosY() const;

    AntStatus GetAntStatus() const;

    void SetAntStatus(const AntStatus s);

    void SetViewRadius(const int n);

    int GetViewRadius() const;

    size_t GetViewSize() const;

    void SetMapSize(const int n);

    int GetMapSize() const;

    void SetVisibleMap(std::string &s);

    const std::string &GetVisibleMap() const;

    std::string &GetVisibleMap();

    void SetVisibleDynMap(std::string &s);

    const std::string &GetVisibleDynMap() const;

    std::string &GetVisibleDynMap();

    void SetNumberOfMessages(const int n);

    int GetNumberOfMessages() const;

    void SetMessage(const int value, const BoardKey bk);

    const std::vector<int> &GetStateMessage(const BoardKey key) const;

};

#endif // CSTATE_H
