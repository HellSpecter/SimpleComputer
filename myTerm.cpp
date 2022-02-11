#include "myTerm.h"

int mt_clearScreen() {
    std::cout << "\E[H\E[J";
    mt_gotoXY(1, 1);
    // == clear
    return 0;
}

int mt_gotoXY(int row, int column) {
    int rows, cols;
    mt_getScreenSize(&rows, &cols);
    if(row >= 0 && row <= rows && column >= 0 && column <= cols) {
        std::cout << "\E[" << row << ";" << column << "H";
        return 0;
    } else {
        return -1;
    }
}

int mt_getScreenSize(int* rows, int* cols) {
    struct winsize windowSize;
    if(!ioctl(1, TIOCGWINSZ, &windowSize)) {
        *rows = windowSize.ws_row;
        *cols = windowSize.ws_col;
        return 0;
    }
    else {
        return -1;
    }
}

int mt_setForeground(COLORS color) {
    if(color >= BLACK and color <= WHITE) {
        std::cout << "\E[3" << color << "m";
        return 0;
    } else {
        return -1;
    }
}

int mt_setBackground(COLORS color) {
    if(color >= BLACK and color <= WHITE) {
        std::cout << "\E[4" << color << "m";
        return 0;
    } else {
        return -1;
    }
}



//cursor_invisible=\E[?25l\E[?1c,
//cursor_visible=\E[?25h\E[?8c,
//set_a_background=\E[4%p1%dm,
//set_a_foreground=\E[3%p1%dm,
