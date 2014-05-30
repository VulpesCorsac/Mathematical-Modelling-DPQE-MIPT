#include "State.h"
#include <string.h>

CState::CState()
:   m_AntPosX(0)
,   m_AntPosY(0)
,   m_AntStatus(AsUnknown)
,   m_MapSize(0)
,   m_ViewRadius(0)
,   m_NumberOfMessages(0)
{
}


void CState::SetPosX(const int x)
{
    m_AntPosX = x;
}

int CState::GetPosX() const
{
    return m_AntPosX;
}

void CState::SetPosY(const int y)
{
    m_AntPosY = y;
}

int CState::GetPosY() const
{
    return m_AntPosY;
}

AntStatus CState::GetAntStatus() const
{
    return m_AntStatus;
}

void CState::SetAntStatus(const AntStatus s)
{
    m_AntStatus = s;
}

void CState::SetViewRadius(const int n)
{
    m_ViewRadius = n;
}

int CState::GetViewRadius() const
{
    return m_ViewRadius;
}

size_t CState::GetViewSize() const
{
    return ((m_ViewRadius * 2) + 1) * ((m_ViewRadius * 2) + 1);
}

void CState::SetMapSize(const int n)
{
    m_MapSize = n;
}

int CState::GetMapSize() const
{
    return m_MapSize;
}

void CState::SetVisibleMap(std::string &s)
{
    m_VisibleMap = s;
}

const std::string &CState::GetVisibleMap() const
{
    return m_VisibleMap;
}

std::string &CState::GetVisibleMap()
{
    return m_VisibleMap;
}

void CState::SetVisibleDynMap(std::string &s)
{
    m_VisibleDynMap = s;
}

const std::string &CState::GetVisibleDynMap() const
{
    return m_VisibleDynMap;
}

std::string &CState::GetVisibleDynMap()
{
    return m_VisibleDynMap;
}

void CState::SetNumberOfMessages(const int n)
{
    m_NumberOfMessages = n;
}

int CState::GetNumberOfMessages() const
{
    return m_NumberOfMessages;
}

void CState::SetMessage(const int value, const BoardKey bk)
{
    m_Messages[bk].push_back(value);
}

const std::vector<int> &CState::GetStateMessage(const BoardKey key) const
{
    return m_Messages[key];
}
