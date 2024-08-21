#include <stdio.h>
#include <TXLib.h>
#include <math.h>

const int SS_INF_ROOTS = -1;
const int SS_NO_ROOTS  =  0;
const int SS_ONE_ROOT  =  1;
const int SS_TWO_ROOTS =  2;

const int firstTest = 0;

const int a_coeff     = 0;
const int b_coeff     = 1;
const int c_coeff     = 2;
const int x1_expected = 3;
const int x2_expected = 4;

int SolveLine (double b, double c, double *x1);
int SolveSquare (double a, double b, double c, double *x1, double *x2);

bool CompareEps(double a);

void input (double *a, double *b, double *c);
void output(int nRoots, double x1, double x2);
void BufferClear();

void swapDouble (double *a, double *b);

int Test(int nTest, double a, double b, double c, double x1_expected, double x2_expected, int nRoots_expected);

struct coeffsStruct
{
    double a;
    double b;
    double c;
    double x1_expected;
    double x2_expected;
    int nRoots_expected;
};

void CreateTests (coeffsStruct tests[]);

void AllTests(coeffsStruct tests[], int sz);


int main()
{
    //double a = NAN, b = NAN, c = NAN;

    //input(&a, &b, &c);

    //assert(isfinite(a));
    //assert(isfinite(b));
    //assert(isfinite(c));

    //int nRoots = 0;
    //double x1 = NAN, x2 = NAN;

    //nRoots = SolveSquare(a, b, c, &x1, &x2);

    //output(nRoots, x1, x2);

    coeffsStruct tests[1] = {};

    int sz = 1;

    CreateTests(tests);

    AllTests(tests, sz);


    //Test(1, 1, -3, 2, 3, 1, 2);
}

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

void output(int nRoots, double x1, double x2)
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

bool CompareEps(double a)
{
    const double EPS = 0.0001;
    return fabs(a) < EPS;
}

int SolveLine (double b, double c, double *x1)
{
    if (CompareEps(b)) {
            return (CompareEps(c))? SS_INF_ROOTS : SS_NO_ROOTS;
        }
        *x1 = -c/b;
        return SS_ONE_ROOT;
}

int SolveSquare (double a, double b, double c, double *x1, double *x2)
{
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    if (CompareEps(a)) {
        return SolveLine(b, c, x1);
    }
    double disc = b*b - 4*a*c;
    if (disc < 0) {
        return SS_NO_ROOTS;
    }
    if (CompareEps(disc)) {
        *x1 = -b/(2*a);
        return SS_ONE_ROOT;
    }
    double sqrtd = sqrt(disc);
    *x1 = (-b + sqrtd)/(2*a);
    *x2 = (-b - sqrtd)/(2*a);
    return SS_TWO_ROOTS;
}

void BufferClear()
{
    while (getchar() != '\n' && getchar() != EOF) {}
}

int Test(int nTest, double a, double b, double c, double x1_ans, double x2_ans, int nRoots_ans)
{
    double x1 = NAN, x2 = NAN;

    int nRoots = SolveSquare(a, b, c, &x1, &x2);

    if (isfinite(x2_ans) && x1_ans < x2_ans) {
        swapDouble(&x1_ans, &x2_ans);
    }

    if (nRoots != nRoots_ans || !CompareEps(x1-x1_ans) || !CompareEps(x2-x2_ans)) {
        printf("Error Test %d: a = %lg, b = %lg, c = %lg, nRoots = %d, x1 = %lg, x2 = %lg\n"
               "Expected: nRoots = %d, x1 = %lg, x2 = %lg", nTest, a, b, c, nRoots, x1, x2,
               nRoots_ans, x1_ans, x2_ans);
        return -1;
    }
    return 0;
}

void CreateTests (coeffsStruct tests[])
{
    tests[firstTest] = {1, -3, 2, 1, 2, 2};
}

 void AllTests(coeffsStruct tests[], int sz)
 {
       for (int i = 0; i < sz; ++i) {
            if (Test(i+1, tests[i].a, tests[i].b, tests[i].c, tests[i].x1_expected,
                tests[i].x2_expected, tests[i].nRoots_expected) == 0) {
                printf("Test %d completed successfully\n", i+1);
            }
       }
 }

 void swapDouble (double *a, double *b)
 {
    double temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
 }





