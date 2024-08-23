#include <stdio.h>

#include "BufferClear.h"

void BufferClear()
{
    while (getchar() != '\n' && getchar() != EOF) {}
}
