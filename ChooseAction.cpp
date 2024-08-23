#include <stdio.h>

#include "ChooseAction.h"

int choose()
 {
    printf("If you want to solve a square equation enter 1,\n"
           "If you want to run tests enter 0:\n");

    int choice = 0;
    scanf("%d", &choice);

    return choice;
 }
