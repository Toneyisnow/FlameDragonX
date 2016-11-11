//
//  FDRandom.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/20/16.
//
//

#include "FDRandom.hpp"

int FDRandom::valueFromRange(int min, int max)
{
    if (max < min)
    {
        int temp = min;
        min = max;
        max = temp;
    }
    
    int ran = rand() % (max - min) + min;
    return ran;
}

int FDRandom::valueFromRange(FDRange * range)
{
    return valueFromRange(range->getMin(), range->getMax());
}

bool FDRandom::hitWithRate(int rate)
{
    int random = rand() % 100;
    return (random < rate);
    
}
