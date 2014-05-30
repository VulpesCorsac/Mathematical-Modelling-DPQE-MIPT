#ifndef CCOMMAND_H
#define CCOMMAND_H

#include "Boardkey.h"
#include <vector>
#include "MoveDirection.h"

class CCommand
{

private:

    MoveDirection m_CommandMove;

    int m_NumberOfMessages;

    std::vector<int> m_Messages[BkCount];


public:

    CCommand();

    int GetNumberOfMessages() const;

    void SetNumberOfMessages(const int num);

    void SetMessage(const int value, const BoardKey bk);

    const std::vector<int> &GetCommandMessage(const BoardKey key) const;

    MoveDirection GetCommandMove() const;

    void SetCommandMove(MoveDirection n);

};

#endif // CCOMMAND_H
