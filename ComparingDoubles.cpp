#include <math.h>

#include "ComparingDoubles.h"

bool CompareZero(double a)
{
    const double EPS = 0.000001;
    return fabs(a) < EPS;
}
