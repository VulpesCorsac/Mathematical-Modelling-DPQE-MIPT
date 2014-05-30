#ifndef CPLAYERLOOP_H
#define CPLAYERLOOP_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QBasicTimer>
#include "Map.h"
#include "Board.h"
#include <fstream>
#include "Frame.h"

class CItemParser;
class CLogParser;
class CFrame;

class CPlayerLoop : public QGraphicsView
{
Q_OBJECT

private:
    QGraphicsScene *m_Scene;
    QBasicTimer m_FrameTimer;
    int m_FrameTimeout;
    int m_GameStep;
    CMap m_Map;
    CBoard m_Board;
    std::ifstream m_Log;
    CFrame m_Frame;

public:
    CPlayerLoop(QGraphicsScene *scene, QWidget *pgwt = NULL);
    bool InitPlayer(int delay);
    void ShowFrame();

protected:
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent (QKeyEvent* event);

private:
    bool ReadBlockFromStream(std::istream &s, CItemParser *logParser);
    void UpdatePlayer(const CLogParser &logParser);
    void ShowMapInText(const CFrame &frame);
};

#endif // CPLAYERLOOP_H
