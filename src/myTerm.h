#ifndef ARCHITECT_MYTERM_H
#define ARCHITECT_MYTERM_H

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

enum COLORS {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    LIGHT_BLUE,
    WHITE,
};

int mt_clearScreen();
int mt_gotoXY (int row, int column);
int mt_getScreenSize(int* rows, int* cols);
int mt_setForeground(COLORS color);
int mt_setBackground(COLORS color);

#endif //ARCHITECT_MYTERM_H
