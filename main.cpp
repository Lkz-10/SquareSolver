#include <stdio.h>
#include <TXLib.h>
#include <math.h>

#include "ChooseAction.h"
#include "InOutput.h"
#include "Solve.h"
#include "Testing.h"
#include "BufferClear.h"

int main()
{
    if (choose() == 1) {

        BufferClear();

        double a = NAN, b = NAN, c = NAN;

        input(&a, &b, &c);

        assert(isfinite(a));
        assert(isfinite(b));
        assert(isfinite(c));

        int nRoots = 0;
        double x1 = NAN, x2 = NAN;

        nRoots = SolveSquare(a, b, c, &x1, &x2);

        output(nRoots, x1, x2);

    } else {

        CreateTests();
    }
}
