#include "PlayerLoop.h"
#include "PacketParser.h"
#include "LogParser.h"
#include <QtGui>
#include "math.h"
#include <iostream>
#include "Frame.h"
#include <string>
#include <sstream>

const  int picSize = 30;
const float TrapScale = 0.133;
qreal Size = (qreal)picSize/30;

CPlayerLoop::CPlayerLoop(QGraphicsScene *scene, QWidget* pwgt)
    :   QGraphicsView(scene, pwgt)
    ,   m_Scene(scene)
    ,   m_FrameTimeout(200)
    ,   m_GameStep(0)
{
    //srand (QTime::currentTime().msec()); // инициализируем ГСЧ
}
bool CPlayerLoop::InitPlayer(int delay)
{

    m_FrameTimeout = delay;

    m_Log.open("../gamelog.txt");

    if(!m_Log.is_open())
    {        
        std::cerr << "Ошибка открытия файла журнала!!!" << std::endl << std::flush;
        return false;
    }

    m_Scene->addText("Press space for start/stop!");

    show();

    return true;
}

void CPlayerLoop::ShowFrame()
{
    // для простоты удаляем все нарисованные объекты
    m_Scene->clear();
    setBackgroundBrush(QBrush(QColor(255,255,255), QPixmap("../player/ground.jpg")));     // сделал траву фоном


    int picPosX = 0;
    int picPosY = 0;
    int infoPosY = 1;
    int textPosX = 0;
   // int textPosY = 2;
  //  qreal Size = picSize/30;
    textPosX = m_Map.GetMapSizeX();


    QGraphicsTextItem* Info = m_Scene->addText("Press 'Space' for start/stop \nPress '+'('-') for to increase (decrease) a speed\n(After this press space twice)");
    Info->setPos(picSize * textPosX, picSize*16);

#if 0
    //  рисуем заново
    QGraphicsPixmapItem* ant = m_Scene->addPixmap(QPixmap("../player/worker.png"));
    ant->scale(2, 2);
    ant->setPos(rand() % m_GameStep, rand() % m_GameStep);

#endif

    for(size_t i = 0; i < m_Map.GetNumberOfAnts(); i++)
        {
            CAnt &ant = m_Map.GetAnt(i);
            std::stringstream sstream;
            sstream  << "AntPosX = "<< ant.GetAntPosX() << ", AntPosY = "<< ant.GetAntPosY() << ",  AntStatus = "<<ant.GetAntStatus();
            QString QStr = QString::fromStdString(sstream.str());

            switch(ant.GetAntType())
            {
            case AtQueen:
            {
                infoPosY++;
                QGraphicsPixmapItem* Queen = m_Scene->addPixmap(QPixmap("../player/queen.png"));
                Queen->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Queen_info =  m_Scene->addText(QStr);
                Queen_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Queen->scale(Size, Size);
                QGraphicsPixmapItem* Queen2 = m_Scene->addPixmap(QPixmap("../player/queen.png"));
                Queen2->setPos(picSize * textPosX, picSize*infoPosY);
                Queen2->scale(Size, Size);
                QGraphicsTextItem* Queen_name = m_Scene->addText("- Queen");
                Queen_name->setPos(textPosX*(picSize+1)+1, picSize*infoPosY);
                break;
            }
            case  AtWorker:    // 1 - рабочий
            {
                infoPosY++;
                QGraphicsPixmapItem* Worker = m_Scene->addPixmap(QPixmap("../player/worker.jpeg"));
                Worker->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Worker_info =  m_Scene->addText(QStr);
                Worker_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
               Worker->scale(Size, Size);
                QGraphicsPixmapItem* Worker2 = m_Scene->addPixmap(QPixmap("../player/worker.jpeg"));
                Worker2->setPos(picSize * textPosX, picSize*(infoPosY));
                  Worker2->scale(Size, Size);
                QGraphicsTextItem* Worker_name = m_Scene->addText("- Worker");
                Worker_name->setPos(textPosX*(picSize+1)+1, picSize*(infoPosY));
                break;
            }
            case AtScout:      // 2 - разведчик
            {
                infoPosY++;
                QGraphicsPixmapItem* Scout = m_Scene->addPixmap(QPixmap("../player/scout.png"));
                Scout->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Scout_info =  m_Scene->addText(QStr);
                Scout_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Scout->scale(Size, Size);
                QGraphicsPixmapItem* Scout2 = m_Scene->addPixmap(QPixmap("../player/scout.png"));
                Scout2->setPos(picSize * textPosX, infoPosY*picSize);
                 Scout2->scale(Size, Size);
                QGraphicsTextItem* Scout_name = m_Scene->addText("- Scout");
                Scout_name->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                break;
            }
            case AtTracker:       // 3 - следопыт
            {
                infoPosY++;
                QGraphicsPixmapItem* Tracker = m_Scene->addPixmap(QPixmap("../player/tracker.png"));
                Tracker->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Tracker_info =  m_Scene->addText(QStr);
                Tracker_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Tracker->scale(Size, Size);
                QGraphicsPixmapItem* Tracker2 = m_Scene->addPixmap(QPixmap("../player/tracker.png"));
                Tracker2->setPos(picSize * textPosX, infoPosY*picSize);
                   Tracker2->scale(Size, Size);
                QGraphicsTextItem* Tracker_info2 = m_Scene->addText("- Tracker");
                Tracker_info2->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                break;
            }
            case   AtSapper:       // 4 - сапер
            {
                infoPosY++;
                QGraphicsPixmapItem* Sapper = m_Scene->addPixmap(QPixmap("../player/sapper.jpeg"));
                Sapper->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                 Sapper->scale(0.2*Size, Size*0.2);
                QGraphicsTextItem* Sapper_info =  m_Scene->addText(QStr);
                Sapper_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                QGraphicsPixmapItem* Sapper2 = m_Scene->addPixmap(QPixmap("../player/sapper.jpeg"));
                Sapper2->setPos(picSize * textPosX, infoPosY*picSize);
                QGraphicsTextItem* Sapper_info2 = m_Scene->addText("- Sapper");
                Sapper_info2->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                Sapper2->scale(0.2*Size, 0.2*Size);
                break;
            }
            case   AtDoctor:       // 5 - врач
            {
                infoPosY++;
                QGraphicsPixmapItem* Doctor = m_Scene->addPixmap(QPixmap("../player/doctor.png"));
                Doctor->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Doctor_info =  m_Scene->addText(QStr);
                Doctor_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Doctor->scale(Size, Size);
                QGraphicsPixmapItem* Doctor2 = m_Scene->addPixmap(QPixmap("../player/doctor.png"));
                Doctor2->setPos(picSize * textPosX, picSize *infoPosY);
                 Doctor2->scale(Size, Size);
                QGraphicsTextItem* Doctor_info2 = m_Scene->addText("- Doctor");
                Doctor_info2->setPos(textPosX*(picSize+1)+1, picSize*infoPosY);
                break;
            }
            case   AtTutor:       // 6 - воспитатель
            {
                infoPosY++;
                QGraphicsPixmapItem* Tutor = m_Scene->addPixmap(QPixmap("../player/tutor.jpeg"));
                Tutor->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                Tutor->scale(TrapScale*Size, TrapScale*Size);
                QGraphicsTextItem* Tutor_info =  m_Scene->addText(QStr);
                Tutor_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                QGraphicsPixmapItem* Tutor2 = m_Scene->addPixmap(QPixmap("../player/tutor.jpeg"));
                Tutor2->setPos(picSize * textPosX,infoPosY*picSize);
                QGraphicsTextItem* Tutor_info2 = m_Scene->addText("- Tutor");
                Tutor_info2->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                Tutor2->scale(TrapScale*Size, Size*TrapScale);
                break;
            }
            case AtFarmer:       // 7 - фермер
            {
                infoPosY++;
                QGraphicsPixmapItem* Farmer = m_Scene->addPixmap(QPixmap("../player/farmer.png"));
                Farmer->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Farmer_info =  m_Scene->addText(QStr);
                Farmer_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Farmer->scale(Size, Size);
                QGraphicsPixmapItem* Farmer2 = m_Scene->addPixmap(QPixmap("../player/farmer.jpg"));
                Farmer2->setPos(picSize * textPosX, infoPosY*picSize);
                Farmer2->scale(Size, Size);
                QGraphicsTextItem* Farmer_info2 = m_Scene->addText("- Farmer");
                Farmer_info2->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                break;
            }
            case AtHunter:     // 8 - охотник
            {
                infoPosY++;
                QGraphicsPixmapItem* Hunter = m_Scene->addPixmap(QPixmap("../player/hunter.png"));
                Hunter->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Hunter_info =  m_Scene->addText(QStr);
                Hunter_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Hunter->scale(0.188*Size, 0.188*Size);
                QGraphicsPixmapItem* Hunter2 = m_Scene->addPixmap(QPixmap("../player/hunter.jpeg"));
                Hunter2->setPos(picSize * textPosX, infoPosY*picSize);
                QGraphicsTextItem* Hunter_info2 = m_Scene->addText("- Hunter");
                Hunter_info2->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                Hunter2->scale(0.188*Size, 0.188*Size);
                break;
            }
            case  AtManager:      // 9 - завхоз
            {
                infoPosY++;
                QGraphicsPixmapItem* Manager = m_Scene->addPixmap(QPixmap("../player/manager.gif"));
                Manager->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                Manager->scale(0.08*Size, 0.08*Size);
                QGraphicsTextItem* Manager_info =  m_Scene->addText(QStr);
                Manager_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                QGraphicsPixmapItem* Manager2 = m_Scene->addPixmap(QPixmap("../player/manager.gif"));
                Manager2->setPos(picSize * textPosX, picSize *infoPosY);
                QGraphicsTextItem* Manager_info2 = m_Scene->addText("- Manager");
                Manager_info2->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                Manager2->scale(0.08*Size, 0.08*Size);

                break;
            }
            case   AtCowboy:     // 10 - пастух
            {
                infoPosY++;
                QGraphicsPixmapItem* Cowboy = m_Scene->addPixmap(QPixmap("../player/cowboy.png"));
                Cowboy->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Cowboy_info =  m_Scene->addText(QStr);
                Cowboy_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Cowboy->scale(1*Size,Size*0.7);
                QGraphicsPixmapItem* Cowboy2 = m_Scene->addPixmap(QPixmap("../player/cowboy.png"));
                Cowboy2->setPos(picSize * textPosX, picSize *infoPosY);
                QGraphicsTextItem* Cowboy_info2 = m_Scene->addText("- Cowboy");
                Cowboy_info2->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                Cowboy2->scale(1*Size,0.7*Size);
                break;
            }
            case  AtCow:     // 11 - коровка
            {
                infoPosY++;
                QGraphicsPixmapItem* Cow = m_Scene->addPixmap(QPixmap("../player/cow.jpeg"));
                Cow->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Cow_info =  m_Scene->addText(QStr);
                Cow_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Cow->scale(0.1875*Size, 0.1875*Size);

                QGraphicsPixmapItem* Cow2 = m_Scene->addPixmap(QPixmap("../player/cow.jpeg"));
                Cow2->setPos(picSize * textPosX, picSize*infoPosY);
                QGraphicsTextItem* Cow_name = m_Scene->addText("- Cow");
                Cow_name->setPos(textPosX*(picSize+1)+1, picSize*infoPosY);
                Cow2->scale(0.1875*Size, 0.1875*Size);
                break;
            }
            case   AtLion:
            {
                infoPosY++;
                QGraphicsPixmapItem* Lion = m_Scene->addPixmap(QPixmap("../player/lion.png"));
                Lion->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                QGraphicsTextItem* Lion_info =  m_Scene->addText(QStr);
                Lion_info->setPos((textPosX+4)*picSize, picSize*infoPosY);
                Lion->scale(Size, Size);
                QGraphicsPixmapItem* Lion2 = m_Scene->addPixmap(QPixmap("../player/lion.png"));
                Lion2->setPos(picSize * textPosX, picSize *infoPosY);
                Lion2->scale(Size, Size);
                QGraphicsTextItem* Lion_info2 = m_Scene->addText("- Lion");
                Lion_info2->setPos(textPosX*(picSize+1)+1, infoPosY*picSize);
                break;
            }
            case   AtUnknown:
            {
                QGraphicsPixmapItem* Unknown = m_Scene->addPixmap(QPixmap("../player/unknown.png"));
                Unknown->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                break;
            }
            case   AtCount:
            {
                QGraphicsPixmapItem* Count = m_Scene->addPixmap(QPixmap("../player/ant.png"));
                Count->setPos(picSize * (ant.GetAntPosX()), picSize *(ant.GetAntPosY()));
                break;
            }
            }

        }
       infoPosY = 1;
    for(int i=0;i<m_Map.GetMapSizeX()*m_Map.GetMapSizeY();i++)
        {

            switch(m_Map.Cell(picPosX, picPosY))
            {

            case McTrap:
            {
                QGraphicsPixmapItem* Trap = m_Scene->addPixmap(QPixmap("../player/trap.jpeg"));
                Trap->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                Trap->scale(0.133*Size,0.133*Size);

                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }
            case McUnknown:
            {
                QGraphicsPixmapItem* Unknown = m_Scene->addPixmap(QPixmap("../player/unknown.png"));
                Unknown->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }
            case McWater:
            {
                QGraphicsPixmapItem* Water = m_Scene->addPixmap(QPixmap("../player/water.png"));
                Water->setPos(picSize*picPosX, picSize*picPosY);
                Water->scale(Size, Size);
                picPosX = picPosX + 1;
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }
            case McWall:
            {
                QGraphicsPixmapItem* Wall = m_Scene->addPixmap(QPixmap("../player/wall.png"));
                Wall->setPos(picSize*picPosX, picSize*picPosY);
                Wall->scale(Size, Size);
                picPosX = picPosX + 1;
                if(picPosX==m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }
            case McHill:
            {
                QGraphicsPixmapItem* Hill = m_Scene->addPixmap(QPixmap("../player/hill.png"));
                Hill->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                Hill->scale(Size, Size);
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }
            case McGround:
            {
                // сделал траву фоном (строка 43)
                // QGraphicsPixmapItem* Ground = m_Scene->addPixmap(QPixmap("../player/ground.jpg"));
                //  Ground->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }
            case McFood:
            {
                QGraphicsPixmapItem*  Food = m_Scene->addPixmap(QPixmap("../player/food.png"));
                Food->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                Food->scale(Size, Size);
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }

                break;
            }
            case McStick:
            {
                QGraphicsPixmapItem* Stick = m_Scene->addPixmap(QPixmap("../player/stick.png"));
                Stick->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                Stick->scale(Size, Size);
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }
            case McStock:
            {
                QGraphicsPixmapItem* Stock = m_Scene->addPixmap(QPixmap("../player/stock.jpeg"));
                Stock->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                Stock->scale(Size/4, Size/4);
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }

            case McWay:
            {
                QGraphicsPixmapItem* Way = m_Scene->addPixmap(QPixmap("../player/ground.jpg"));
                Way->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }

            case McError:
            {
                QGraphicsPixmapItem* Error = m_Scene->addPixmap(QPixmap("../player/unknown.png"));
                Error->setPos(picSize * picPosX, picSize * picPosY);
                picPosX = picPosX + 1;
                if(picPosX == m_Map.GetMapSizeX())
                {
                    picPosX = 0;
                    picPosY = picPosY + 1;
                }
                break;
            }

            }
        }


    std::stringstream sstream;
    sstream  << "MapSize = "<<m_Map.GetMapSizeX() << "\nGame step = " << m_GameStep;
    QString QStr = QString::fromStdString(sstream.str());
    QGraphicsTextItem* Size_of_Map = m_Scene->addText(QStr);
    Size_of_Map->setPos((m_Map.GetMapSizeX()+1)*picSize, 1);



    // перерисовываем окно вывода
    repaint();

}
void CPlayerLoop::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_FrameTimer.timerId()) //если сработал таймер кадров
    {

        if(!m_Log.is_open())
        {
            std::cerr << "Ошибка открытия файла журнала!!!" << std::endl << std::flush;
            m_FrameTimer.stop();
            return;
        }
        //читаем очередной блок из файла журнала
        //создаем объект - парсер файла жкрнала
        CLogParser logParser;

        //Читаем блок из входного потока, пока не встретится пустая строка, признак конца файла или ошибка в данных

        if(!ReadBlockFromStream(m_Log, &logParser) && !m_Log.eof())
        {
            if(logParser.IsError())
            {
                std::cerr << "Ошибка в CLogParser: " << logParser.GetErrorMessage().c_str() << std::endl << std::flush;
            }
            else
            {
                std::cerr << "Ошибка чтения файла!!!" << std::endl << std::flush;
            }

            m_FrameTimer.stop();
            return;
        }
        else
        {
            // отладочный вывод на консоль прочитанных из файла данных
            // ShowMapInText(logParser.GetFrame());

            if (m_Log.eof())
            {
                std::cerr << "Файл успешно прочитан!!!\n";
                m_FrameTimer.stop();
                return;
            }

            UpdatePlayer(logParser);
            ShowFrame();
        }
    }
}

void CPlayerLoop::UpdatePlayer(const CLogParser &logParser)
{
    // здесь может располагаться какая-нибудь логика, если требуется учитывать предыдущее состояние карты
    // можно сделать проверку, что шаг игры в файле действительно увеличился на 1
    m_Map = logParser.GetFrame().GetMap();
    m_Board = logParser.GetFrame().GetBoard();
    m_GameStep = logParser.GetFrame().GetGameStep();
}

void CPlayerLoop::keyPressEvent(QKeyEvent *event)
{
    // std::cerr << "Нажали кнопку!!!" << std::endl << std::flush;
    if (event->key() == Qt::Key_Plus)
    {
        m_FrameTimeout = m_FrameTimeout + 50;
    }
    if (event->key() == Qt::Key_Minus)
    {
        if(m_FrameTimeout>0)
        {
            if(m_FrameTimeout>50)
                m_FrameTimeout = m_FrameTimeout - 50;
            else    m_FrameTimeout = m_FrameTimeout - 10;
        }

    }
    if (event->key() == Qt::Key_Space)
    {

        if (m_FrameTimer.isActive())
        {
            m_FrameTimer.stop();
        }
        else
        {
            m_FrameTimer.start(m_FrameTimeout, this);
        }
    }

    QGraphicsView::keyPressEvent(event);
}

bool CPlayerLoop:: ReadBlockFromStream(std::istream &s, CItemParser *logParser)
{

    //создаем объект - парсер пакета и передаем ему указатель на парсер строк пакета
    // При выходе из функции он уничтожится.
    CPacketParser parser(logParser);

    for(;;)
    {
        char c;
        if(!s.get(c)) // стандартный метод класса std::istream для чтения одного байта из файла
        {             // возвращает false в случае ошибки работы с файлом
            return false;
        }
        else
        {
            if(!parser.AddByte(c))
            {
                return !logParser->IsError(); // если встретилась пустая строка,
            }                                 // возвращаем инвертированный признак ошибки
        }
    }
}

void CPlayerLoop::ShowMapInText(const CFrame &frame)
{
    const CMap &map = frame.GetMap();
    // печатаем карту
    system("clear");
    for (int rowNumber = 0; rowNumber < map.GetMapSizeY(); ++rowNumber)
    {
        for (int colNumber = 0; colNumber < map.GetMapSizeX(); ++colNumber)
        {
            bool antIsHere = false;
            for (size_t antNumber = 0; antNumber < map.GetNumberOfAnts(); ++antNumber)
            {
                const CAnt &a = map.GetAnt(antNumber);
                if((colNumber == a.GetAntPosX()) && (rowNumber == a.GetAntPosY()) && !a.AntIsBanned() && !a.AntIsWinner())
                {
                    std::cout << a.GetAntName()[0];
                    antIsHere = true;
                    break;
                }
                else
                {
                    continue;
                }
            }
            if (!antIsHere)
            {
                std::cout << (char)map.Cell(colNumber, rowNumber);
            }
        }
        std::cout << std::endl;
    }

    for (size_t antNumber = 0; antNumber < map.GetNumberOfAnts(); ++antNumber)
    {
        const CAnt &a = map.GetAnt(antNumber);
        if (!a.AntIsBanned() && !a.AntIsWinner())
        {
            std::cout  << "Муравей " << a.GetAntName()
                       << " по профессии " << AntTypeToString(a.GetAntType()) << " "
                       << AntStatusToString(a.GetAntStatus()) << "!" << std::endl
                       << "Находится в клетке X = " << a.GetAntPosX() << " Y = " << a.GetAntPosY()
                       << std::endl << std::flush;
        }
        else
        {
            std::cout  << "Муравей " << a.GetAntName()
                       << " по профессии " << AntTypeToString(a.GetAntType()) << " "
                       << AntStatusToString(a.GetAntStatus()) << "!" << std::endl;
        }

    }

    std::cout  << "Доска объявлений: " << std::endl;
    frame.GetBoard().PrintBoard();
    std::cout << std::flush;
}
