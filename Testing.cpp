#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "Testing.h"
#include "Solve.h"
#include "Swap.h"
#include "ComparingDoubles.h"
#include "Globals.h"
#include "OutputColours.h"

const int global_nTests = 10;

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
               "Expected: nRoots = %d, x1 = %lg, x2 = %lg\n" COLOUR_RESET,
               nTest, structData->a, structData->b, structData->c, nRoots, x1, x2,
               structData->nRoots_expected, structData->x1_expected, structData->x2_expected);

        return -1;
    }
    return 0;
}

void CreateTests ()
{
    coeffsStruct tests[global_nTests] = {};

    int line_sz = 50;

    char* line = (char*) calloc(line_sz, sizeof(char));
    assert(line);

    FILE* file_ptr = fopen("TestData.txt","r");

    if (file_ptr == NULL) printf(RED "Error while opening file\n" COLOUR_RESET);

    int curr_test = 0;

    while (fgets(line, line_sz, file_ptr) != NULL) {

        assert(curr_test >= 0 && curr_test < global_nTests);

        if (sscanf(line, "%lg %lg %lg %lg %lg %d", &(tests[curr_test].a), &(tests[curr_test].b),
                   &(tests[curr_test].c), &(tests[curr_test].x1_expected), &(tests[curr_test].x2_expected),
                   &(tests[curr_test].nRoots_expected)) != 6) {

            printf(RED "Error while reading data for test %d\n" COLOUR_RESET, curr_test+1);
        }
        curr_test++;
    }

    fclose(file_ptr);
    free(line);

    RunAllTests(tests);
}

void RunAllTests(coeffsStruct tests[])
 {
       int success = 0;

       for (int i = 0; i < global_nTests; ++i) {
            if (Test(i+1, &(tests[i])) == 0) {
                success++;
            }
       }

       if (success == global_nTests) {
            printf(GREEN "All tests completed successfully\n" COLOUR_RESET);
       } else {
            printf(GREEN "%d tests completed successfully\n" COLOUR_RESET, success);
       }
 }

