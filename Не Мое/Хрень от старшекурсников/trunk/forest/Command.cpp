#include "Command.h"

CCommand::CCommand()
:   m_CommandMove(MdUnknown)
,   m_NumberOfMessages(0)
{
}

MoveDirection CCommand::GetCommandMove() const
{
    return m_CommandMove;
}

void CCommand::SetCommandMove(MoveDirection m)
{
    m_CommandMove = m;
}

void CCommand::SetMessage(const int value, const BoardKey bk)
{
    m_Messages[bk].push_back(value);
}

const std::vector<int> &CCommand::GetCommandMessage(const BoardKey key) const
{
    return m_Messages[key];
}

int CCommand::GetNumberOfMessages() const
{
    return m_NumberOfMessages;
}

void CCommand::SetNumberOfMessages(const int num)
{
    m_NumberOfMessages = num;
}
