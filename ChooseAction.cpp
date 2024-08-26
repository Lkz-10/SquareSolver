#include <stdio.h>

#include "ChooseAction.h"
#include "Globals.h"

int choose()
 {
    printf(BLUE "If you want to solve a square equation enter 1,\n"
           "If you want to run tests enter 0:\n" RESET_COLOUR);

    int choice = 0;
    scanf("%d", &choice);

    return choice;
 }
