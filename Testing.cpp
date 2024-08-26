#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "Testing.h"
#include "Solve.h"
#include "Swap.h"
#include "ComparingDoubles.h"
#include "Globals.h"

const int nTests = 10;

int Test(int nTest, struct coeffsStruct* structData)
{
    double x1 = NAN, x2 = NAN;

    int nRoots = SolveSquare(structData->a, structData->b, structData->c, &x1, &x2);

    if (isfinite(structData->x2_expected) && structData->x1_expected < structData->x2_expected) {
        swapDouble(&(structData->x1_expected), &(structData->x2_expected));
    }

    bool x1_nan = false, x2_nan = false;

    if (!isfinite(x1) && !isfinite(structData->x1_expected)) x1_nan = true;
    if (!isfinite(x2) && !isfinite(structData->x2_expected)) x2_nan = true;

    if (nRoots != structData->nRoots_expected || (!x1_nan && !CompareZero(x1 - structData->x1_expected)) ||
        (!x2_nan && !CompareZero(x2 - structData->x2_expected))) {

        printf(RED "Error Test %d: a = %lg, b = %lg, c = %lg, nRoots = %d, x1 = %lg, x2 = %lg\n"
               "Expected: nRoots = %d, x1 = %lg, x2 = %lg\n" RESET_COLOUR, nTest, structData->a, structData->b, structData->c,
               nRoots, x1, x2, structData->nRoots_expected, structData->x1_expected, structData->x2_expected);

        return -1;
    }
    return 0;
}

void CreateTests ()
{
    coeffsStruct tests[nTests] = {};

    char line[100];
    FILE* ptr;
    ptr = fopen("TestData.txt","r");

    if (ptr == NULL) printf(RED "Error while opening file\n" RESET_COLOUR);

    int i = 0;

    while (fgets(line, sizeof(line), ptr) != NULL) {

        assert(i >= 0 && i < nTests);

        if (sscanf(line, "%lg %lg %lg %lg %lg %d", &(tests[i].a), &(tests[i].b), &(tests[i].c),
            &(tests[i].x1_expected), &(tests[i].x2_expected), &(tests[i].nRoots_expected)) != 6) {

            printf(RED "Error while reading data for test %d\n" RESET_COLOUR, i+1);
        }
        i++;
    }

    fclose(ptr);

    RunAllTests(tests);
}

void RunAllTests(coeffsStruct tests[])
 {
       int success = 0;

       for (int i = 0; i < nTests; ++i) {
            if (Test(i+1, &(tests[i])) == 0) {
                success++;
            }
       }

       if (success == nTests) {
            printf(GREEN "All tests completed successfully\n" RESET_COLOUR);
       } else {
            printf(GREEN "%d tests completed successfully\n" RESET_COLOUR, success);
       }
 }

