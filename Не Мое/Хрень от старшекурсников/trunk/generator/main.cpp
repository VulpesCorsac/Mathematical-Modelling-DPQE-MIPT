#include "GeneratorLoop.h"


int main(int argc, char *argv[])
{

    const std::string defaultMapFilename = "../map.txt";
    const size_t defaultMapSize = 30;
    const size_t defaultWaterSize = 150;
    const size_t defaultFoodAmount = 1;
    const size_t defaultStickAmount = 0;
    const size_t defaultAntDistance = 8;
    const size_t defaultTrapAmount = 0;

    CGeneratorLoop generator;

    generator.GeneratorLoop(defaultMapSize, defaultWaterSize, defaultFoodAmount, defaultStickAmount, defaultAntDistance, defaultTrapAmount);

    generator.WriteMap(defaultMapFilename);



    return 0;
}

