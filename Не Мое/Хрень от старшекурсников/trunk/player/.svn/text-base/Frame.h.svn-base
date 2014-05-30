#ifndef CFRAME_H
#define CFRAME_H

#include "Map.h"
#include "Board.h"

class CFrame
{
private:

    int m_GameStep;
    size_t m_MapSize;
    CMap m_Map;
    int m_FoodInHill;
    int m_FoodInStock;
    int m_StickInHill;
    int m_ChildrenGrownup;
    int m_NumberOfAnts;
    int m_NumberOfMessages;
    CBoard m_Board;

public:

    CFrame();

    int GetGameStep() const;

    void SetGameStep(const int s);

    size_t GetMapSize() const;

    void SetMapSize(const int m);

    const CMap &GetMap() const;

    CMap &GetMap();

    int GetFoodInHill() const;

    void SetFoodInHill(const int f);

    int GetFoodInStock() const;

    void SetFoodInStock(const int f);

    int GetStickInHill() const;

    void SetStickInHill(const int s);

    int GetChildrenGrownup() const;

    void SetChildrenGrownup(const int c);

    int GetNumberOfAnts() const;

    void SetNumberOfAnts(const int m);

    const CBoard &GetBoard() const;

    CBoard &GetBoard();

    int GetNumberOfMessages() const;

    void SetNumberOfMessages(const int num);

};

#endif // CFRAME_H
