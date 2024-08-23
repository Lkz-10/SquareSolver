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

    printf("Enter the coefficients:\n");

    while (scanf("%lg %lg %lg", a, b, c) != 3) {
        BufferClear();
        printf("Error, Enter three coefficients:\n");
    }

}

void output (int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case SS_NO_ROOTS:
            printf("No roots\n");
            break;

        case SS_ONE_ROOT:
            printf("One root, x = %lg\n", x1);
            break;

        case SS_TWO_ROOTS:
            printf("Two roots, x1 = %lg, x2 = %lg\n", x1, x2);
            break;

        case SS_INF_ROOTS:
            printf("Infinite amount of roots\n");
            break;

        default:
            printf("ERROR\n");
    }
}
