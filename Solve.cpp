#include <assert.h>
#include <math.h>

#include "Solve.h"
#include "ComparingDoubles.h"
#include "Globals.h"

int SolveSquare (double a, double b, double c, double* x1, double* x2)
{
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    if (CompareZero(a)) {              // a == 0
        return SolveLine(b, c, x1);
    }
    if (CompareZero(b)) {              // b == 0
        return SolveAC(a, c, x1, x2);
    }
    if (CompareZero(c)) {              // c == 0
        return SolveAB(a, b, x1, x2);
    }
    double disc = b*b - 4*a*c;
    if (disc < 0) {
        return SS_NO_ROOTS;
    }
    if (CompareZero(disc)) {           // disc == 0
        *x1 = -b/(2*a);
        return SS_ONE_ROOT;
    }
    double sqrtd = sqrt(disc);

    *x1 = (-b + sqrtd)/(2*a);
    *x2 = (-b - sqrtd)/(2*a);

    return SS_TWO_ROOTS;
}

int SolveLine (double b, double c, double* x1)
{
    if (CompareZero(b)) {                                         // b == 0
            return (CompareZero(c))? SS_INF_ROOTS : SS_NO_ROOTS;  // c == 0
        }
        *x1 = 0 - c/b;
        return SS_ONE_ROOT;
}

int SolveAC (double a, double c, double* x1, double* x2)   // if b == 0
{
    if (CompareZero(c)) {                                  //if c == 0 too
        *x1 = 0;
        return SS_ONE_ROOT;
    }
    if (-c/a < 0) {
        return SS_NO_ROOTS;
    }

    *x1 = sqrt(-c/a);
    *x2 = -*x1;

    return SS_TWO_ROOTS;
}

int SolveAB (double a, double b, double* x1, double* x2)
{
    *x1 = 0;
    *x2 = -b/a;

    return SS_TWO_ROOTS;
}
