#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

//#include "ChooseAction.h"
#include "InOutput.h"
#include "Solve.h"
#include "Testing.h"
#include "Globals.h"

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        printf(RED "Error, too little arguments\n" COLOUR_RESET);
        return 0;
    }
    if (strcmp(argv[1], "equation") == 0) {

        double a = NAN, b = NAN, c = NAN;

        input(&a, &b, &c);

        assert(isfinite(a));
        assert(isfinite(b));
        assert(isfinite(c));

        int nRoots = 0;
        double x1 = NAN, x2 = NAN;

        nRoots = SolveSquare(a, b, c, &x1, &x2);

        output(nRoots, x1, x2);

    } else if (strcmp(argv[1], "test") == 0) {

        CreateTests();
    }
}
