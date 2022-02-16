#include "myBigChars.h"
#include "myTerm.h"

int bc_printA(char* str) {
    std::cout << "\E(0" << str << "\E(B";
    return 0;
}
// `afgijklmnopqrstuvwxyz{|}~
// ◆▒°±␋┘┐┌└┼─├┤┴┬│≤≥π≠£·

int bc_box(int row, int col, int width, int height) {
    mt_gotoXY(row, col);
    mt_setForeground(BLUE);
    char* temp = new  char[width + 2];
    for(int i = 1; i < width + 1; i++) {
        temp[i] = 'q';
    }
    // верх
    temp[0] = 'l';
    temp[width + 1] = 'k';
    bc_printA(temp);
    // лево, право
    char* temp1 = new char[1];
    temp1[0] = 'x';
    for(int i = row + 1; i < row + height + 1; i++) {
        mt_gotoXY(i, col);
        bc_printA(temp1);
        mt_gotoXY(i, col + width + 1);
        bc_printA(temp1);
    }
    // низ
    mt_gotoXY(height + row + 1, col);
    temp[0] = 'm';
    temp[width + 1] = 'j';
    bc_printA(temp);
    mt_gotoXY(row + height + 2, col + width + 2);
    mt_setForeground(WHITE);
    return 0;
}

int bc_printBigChar(BIGCHARS charIndex, int row, int col, COLORS bgColor, COLORS fgColor) {
    mt_setBackground(bgColor);
    mt_setForeground(fgColor);
    char* temp = new char[8];
    for(int i = 0, k = 0, index = 0; i < 8; i++) {
        if(i == 4) index = 1;
        for(int j = 0; j < 8; j++, k++) {
            ((bigChars[charIndex][index] >> k) & 0x1) == 0 ? temp[j] = ' ' : temp[j] = 'a';
        }
        mt_gotoXY(row + i, col);
        bc_printA(temp);
    }
    mt_setBackground(BLACK);
    mt_setForeground(WHITE);
    mt_gotoXY(18, 0);
    return 0;
}

int bc_setBigCharPos(int *big, int row, int col, bool value) {
    if(row < 0 || row > 7 || col < 0 || col > 7)
        return -1;
    if(value)
        big[row / 4] |= 1 << ((row % 4) * 8 + col);
    else
        big[row / 4] &= ~(1 << ((row % 4) * 8 + col));
    return 0;
}

int bc_getBigCharPos(int *big, int row, int col, bool *value) {
    if(row < 0 or row > 7 or col < 0 or col > 7)
        return -1;

    ((big[row / 4] >> ((row % 4) * 8 + col)) & 0x1) == 1 ? *value = true : *value = false;

    return 0;
}

int bc_bigCharWrite(int fileDescriptor, int *big, int count) {
    write(fileDescriptor, big, sizeof(unsigned int) * 2 * count);
    close(fileDescriptor);
    return 0;
}

int bc_bigCharRead(int fileDescriptor, int *big, int need_count, int *count) {
    read(fileDescriptor, big, sizeof(unsigned int) * 2 * need_count);
    close(fileDescriptor);
    return 0;
}