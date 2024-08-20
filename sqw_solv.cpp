#include <stdio.h>
#include <TXLib.h>
#include <math.h>

const int SS_INF_ROOTS = -1;
const int SS_NO_ROOTS = 0;
const int SS_ONE_ROOT = 1;
const int SS_TWO_ROOTS = 2;

int SolveLine (double b, double c, double *x1);
int SolveSquare (double a, double b, double c, double *x1, double *x2);

bool CompareEps(double a);

void input (double *a, double *b, double *c);
void output(int nRoots, double x1, double x2);

int main()
{
    double a, b, c;
    a = b = c = NAN;

    input(&a, &b, &c);

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    int nRoots = 0;
    double x1, x2;
    x1 = x2 = NAN;

    nRoots = SolveSquare(a, b, c, &x1, &x2);

    output(nRoots, x1, x2);
}

void input (double *a, double *b, double *c)
{
    assert(a);
    assert(b);
    assert(c);
    assert(a != b && a != c && b != c);
    printf("Enter the coefficients:\n");
    while (scanf("%lg %lg %lg", a, b, c) != 3) {
        while (getchar() != '\n' && getchar() != EOF) {}
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


