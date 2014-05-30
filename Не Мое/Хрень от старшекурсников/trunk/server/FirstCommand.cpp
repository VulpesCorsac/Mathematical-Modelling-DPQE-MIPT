#include "FirstCommand.h"

CFirstCommand::CFirstCommand()
:   m_Type(AtUnknown)
{
}

const std::string &CFirstCommand::GetName() const
{
    return m_Name;
}

void CFirstCommand::SetName(const std::string &n)
{
    m_Name = n;
}

AntType CFirstCommand::GetType() const
{
    return m_Type;
}

void CFirstCommand::SetType(const AntType t)
{
    m_Type = t;
}
