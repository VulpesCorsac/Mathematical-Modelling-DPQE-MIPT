#include "Board.h"
#include  <iostream>
#include <stdlib.h>
#include <vector>

CBoard::CBoard()
{
}

const std::vector<int> &CBoard::GetMessage(BoardKey bk) const
{
    return m_Messages[bk];
}

std::vector<int> &CBoard::GetMessage(BoardKey bk)
{
    return m_Messages[bk];
}

void CBoard::AddValue(const int v, BoardKey bk)
{
    m_Messages[bk].push_back(v);
}

void CBoard::AddMessage(const std::vector<int>  &a, BoardKey bk)
{
    for (size_t num = 0; num < a.size(); num++)
    {
        m_Messages[bk].push_back(a[num]);
    }
}

void CBoard::ReplaceMessage(const std::vector<int>  &a, BoardKey bk)
{
    m_Messages[bk].clear();

    for (size_t num = 0; num < a.size(); num++)
    {
        m_Messages[bk].push_back(a[num]);
    }
}

void CBoard::PrintBoard() const
{
    for(int i = 0; i < BkCount; i++)
    {
        BoardKey bk = (BoardKey)i;
        std::cout << BoardKeyToString(bk) << " : ";
        for(size_t number = 0; number <  m_Messages[bk].size(); ++number)
        {
             std::cout << m_Messages[bk][number] << " ";
        }
        std::cout << std::endl;
    }
 }

void CBoard::DeleteMessage(const BoardKey key)
{
    m_Messages[key].clear();
}

void CBoard::DeleteAllMessages()
{
    for(int i = 0; i < BkCount; i++)
    {
        m_Messages[(BoardKey)i].clear();
    }
}

bool CBoard::FindMessage(BoardKey bk, const int x, const int y) const
{
    for(size_t k = 0; k < m_Messages[bk].size(); ++k)
    {
        if ((m_Messages[bk][k] == x) && (m_Messages[bk][k + 1] == y))
        {
            return true;
        }
    }

    return false;
}

