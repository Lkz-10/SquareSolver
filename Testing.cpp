#include <stdio.h>
#include <math.h>

#include "Testing.h"
#include "Solve.h"
#include "Swap.h"
#include "ComparingDoubles.h"
#include "Globals.h"

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

        printf("Error Test %d: a = %lg, b = %lg, c = %lg, nRoots = %d, x1 = %lg, x2 = %lg\n"
               "Expected: nRoots = %d, x1 = %lg, x2 = %lg\n", nTest, structData->a, structData->b, structData->c,
               nRoots, x1, x2, structData->nRoots_expected, structData->x1_expected, structData->x2_expected);

        return -1;
    }
    return 0;
}

void CreateTests ()
{
    coeffsStruct tests[] = {

    {.a = 1,      .b = -3,       .c = 2,      .x1_expected = 1,          .x2_expected = 2,          //��� �����
     .nRoots_expected = 2},


    {.a = 0,      .b = 0,        .c = 0,      .x1_expected = NAN,        .x2_expected = NAN,        //���������� ������
     .nRoots_expected = SS_INF_ROOTS},


    {.a = 2,      .b = 4,        .c = 2,      .x1_expected = -1,         .x2_expected = NAN,        //1 ������, D = 0
     .nRoots_expected = 1},

    {.a = 18,     .b = 4,        .c = 41,     .x1_expected = NAN,        .x2_expected = NAN,        //0 ������, D < 0
     .nRoots_expected = 0},

    {.a = 0,      .b = 16,       .c = 21,     .x1_expected = -1.3125,    .x2_expected = NAN,        //��������
     .nRoots_expected = 1},

    {.a = 2.1,    .b = 3.85,     .c = -16.84, .x1_expected = 2.059795,   .x2_expected = -3.893129,  //�������
     .nRoots_expected = 2},

    {.a = 0.0008, .b = 0.000016, .c = -0.032, .x1_expected = 6.31456322, .x2_expected = -6.3345632, //��������� ��������
     .nRoots_expected = 2},

    {.a = 4,      .b = 0,        .c = 60,     .x1_expected = NAN,        .x2_expected = NAN,        //b=0, 0 ������
     .nRoots_expected=0},

    {.a = 125,    .b = 0,        .c = -64,    .x1_expected = 0.7155418,  .x2_expected = -0.7155418, //b=0, 2 �����
     .nRoots_expected=2},

    {.a = 45,     .b = 12,       .c = 0,      .x1_expected = 0,          .x2_expected = -0.266667,  //c=0, 2 �����
     .nRoots_expected = 2}
    };

    RunAllTests(tests);
}

void RunAllTests(coeffsStruct tests[])
 {
       const int nTests = 10;
       int success = 0;

       for (int i = 0; i < nTests; ++i) {
            if (Test(i+1, &(tests[i])) == 0) {
                success++;
            }
       }

       if (success == nTests) {
            printf("All tests completed successfully\n");
       } else {
            printf("%d tests completed successfully\n", success);
       }
 }
