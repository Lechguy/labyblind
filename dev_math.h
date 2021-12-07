#ifndef __DEV_MATH_H__
#define __DEV_MATH_H__

namespace Dev  {
namespace Math {

float
BoundFloatValue(float value, float min, float max);

int
BoundIntValue(int value, int min, int max);

} /* Math */
} /* Dev */

#endif /*__DEV_MATH_H__ */