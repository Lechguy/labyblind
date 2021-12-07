#include "dev_math.h"
#include <cmath>
#include <iostream>

namespace Dev  {
namespace Math {

float
BoundFloatValue(float value, float min, float max)
{
    return std::min<float>(std::max<float>(value, min), max);
}

int
BoundIntValue(int value, int min, int max)
{
    return std::min<int>(std::max<int>(value, min), max);
}

} /* Math */
} /* Dev */