#ifndef CGENERATORLOOP_H
#define CGENERATORLOOP_H

#include "Map.h"
#include "vector"

class CGeneratorLoop
{
private:

    CMap m_Map;
    int *m_length;
    std::vector <int> m_AbleCoordinates;


public:    

    CGeneratorLoop();

    void GeneratorLoop(size_t mapSize, size_t waterSize, size_t foodAmount, size_t stickAmount, size_t antDistance, size_t trapAmount);

    void WriteMap(const std::string &fileName);

    const int * GetLinkOfAbleCoordinates ();

private:

    void GenerateMap(size_t sizeX, size_t sizeY, size_t sizeW, size_t foodAmount, size_t stickAmount, size_t antDistance, size_t trapAmount);

    bool CheckMap(size_t foodAmount, size_t stickAmount, size_t trapAmount);

};

#endif // CGENERATORLOOP_H
