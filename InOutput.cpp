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

    printf(BLUE "Enter the coefficients:\n" RESET_COLOUR);

    while (scanf("%lg %lg %lg", a, b, c) != 3) {
        BufferClear();
        printf(RED "Error, Enter three coefficients:\n" RESET_COLOUR);
    }

}

void output (int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case SS_NO_ROOTS:
            printf(GREEN "No roots\n" RESET_COLOUR);
            break;

        case SS_ONE_ROOT:
            printf(GREEN "One root, x = %lg\n" RESET_COLOUR, x1);
            break;

        case SS_TWO_ROOTS:
            printf(GREEN "Two roots, x1 = %lg, x2 = %lg\n" RESET_COLOUR, x1, x2);
            break;

        case SS_INF_ROOTS:
            printf(GREEN "Infinite amount of roots\n" RESET_COLOUR);
            break;

        default:
            printf(RED "ERROR\n" RESET_COLOUR);
    }
}
