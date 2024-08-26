#include <stdio.h>

#include "BufferClear.h"

void BufferClear()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
