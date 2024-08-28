#include <stdio.h>

#include "ChooseAction.h"
#include "Globals.h"
#include "OutputColours.h"

int choose()
 {
    printf(BLUE "If you want to solve a square equation enter 1,\n"
           "If you want to run tests enter 0:\n" COLOUR_RESET);

    int choice = 0;
    scanf("%d", &choice);

    return choice;
 }
