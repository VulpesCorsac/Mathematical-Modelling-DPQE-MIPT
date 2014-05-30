#ifndef CBOARD_H
#define CBOARD_H

#include "Boardkey.h"
#include <vector>

class CBoard

{
private:

    BoardKey m_BoardKey;

    std::vector<int> m_Messages[BkCount];

public:

    CBoard();

    const std::vector<int> &GetMessage(BoardKey bk) const;

    std::vector<int> &GetMessage(BoardKey bk);

    void AddMessage(const std::vector<int> &a, BoardKey bk);

    void AddValue(const int v, BoardKey bk);

    void ReplaceMessage(const std::vector<int> &a, BoardKey bk);

    void PrintBoard() const;

    void DeleteMessage(const BoardKey key);

    void DeleteAllMessages();

    bool FindMessage(BoardKey bk, const int x, const int y) const;


};

#endif // CBOARD_H
