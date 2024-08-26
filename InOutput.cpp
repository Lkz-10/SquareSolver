#include <stdio.h>
#include <assert.h>

#include "InOutput.h"
#include "Globals.h"
#include "BufferClear.h"

void input (double *a, double *b, double *c)
{
    assert(a);
    assert(b);
    assert(c);
    assert(a != b && a != c && b != c);

    printf(BLUE "Enter the coefficients:\n" COLOUR_RESET);

    while (scanf("%lg %lg %lg", a, b, c) != 3) {
        BufferClear();
        printf(RED "Error, Enter three coefficients:\n" COLOUR_RESET);
    }

}

void output (int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case SS_NO_ROOTS:
            printf(GREEN "No roots\n" COLOUR_RESET);
            break;

        case SS_ONE_ROOT:
            printf(GREEN "One root, x = %lg\n" COLOUR_RESET, x1);
            break;

        case SS_TWO_ROOTS:
            printf(GREEN "Two roots, x1 = %lg, x2 = %lg\n" COLOUR_RESET, x1, x2);
            break;

        case SS_INF_ROOTS:
            printf(GREEN "Infinite amount of roots\n" COLOUR_RESET);
            break;

        default:
            printf(RED "ERROR\n" COLOUR_RESET);
    }
}
