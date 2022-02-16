#ifndef ARCHITECT_MYBIGCHARS_H
#define ARCHITECT_MYBIGCHARS_H

#include "myTerm.h"
#include <iterator>

const unsigned int bigChars[18][2]= {
                {3'890'741'118,  2'130'700'263},  // 0
                {943'602'744,    943'208'504},    // 1
                {1'894'252'414,  4'294'903'580},  // 2
                {2'145'451'903,  2'147'475'680},  // 3
                {4'286'019'447,  1'886'417'151},  // 4
                {2'131'230'719,  2'130'698'495},  // 5
                {2'131'230'590,  2'130'700'287},  // 6
                {1'893'793'791,  471'604'280},    // 7
                {2'129'133'438,  2'129'127'399},  // 8
                {4'293'394'302,  2'130'698'494},  // 9
                {3'890'741'118,  3'890'741'247},  // A
                {2'145'910'655,  2'145'904'615},  // B
                {1'32'644'734,   2'130'700'039},  // C
                {3'890'741'119,  2'147'477'479},  // D
                {1'057'488'895,  4'294'903'615},  // E
                {1'057'488'895,  117'901'119},    // F
                {2'115'508'224,  1'579'134},      // +
                {2'113'929'216,  126},            // -
        };

enum BIGCHARS {
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
    NINE, A, B, C, D, E, F, PLUS, MINUS,
};

int bc_printA(char* str);
int bc_box(int row, int col, int width, int height);
int bc_printBigChar(BIGCHARS bigChar, int row, int col, COLORS bgColor, COLORS fgColor);
int bc_setBigCharPos(int *big, int x, int y, bool value);
int bc_getBigCharPos(int *big, int x, int y, bool *value);
int bc_bigCharWrite(int fileDescriptor, int *big, int count);
int bc_bigCharRead(int fileDescriptor, int *big, int need_count, int *count);

#endif //ARCHITECT_MYBIGCHARS_H
