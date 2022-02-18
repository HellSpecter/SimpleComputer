#ifndef ARCHITECT_MYSIMPLECOMPUTER_H
#define ARCHITECT_MYSIMPLECOMPUTER_H
// маски для флагов
#define OPERATION_OVERFLOW 1
#define DIVISION_BY_ZERO 2
#define OUT_OF_BOUNDS 3
#define CLOCK_PULSE_IGNORE 4
#define INVALID_COMMAND 5

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class mySC {
protected:
    const static int SIZE = 100;
    int ram[SIZE];
    unsigned int flags;
    int instructionCounter;

public:
    const int COMMANDS[38] = {
            0xA,  0xB, 0x14, 0x15, 0x1E, 0x1F, 0x20, 0x21,
            0x28, 0x29, 0x2A, 0x2B, 0x33, 0x34, 0x35, 0x36,
            0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
            0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
            0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C};

    mySC();

    int printAll(int currentIndex);
    int sc_memoryInit();
    int sc_memorySet(int address, int value);
    int sc_memoryGet(int address, int* value);
    int sc_memorySave(const char* filename);
    int sc_memoryLoad(const char* filename);
    int sc_regInit();
    int sc_regSet(int flagName, bool value);
    int sc_regGet(int flagName, unsigned int* value);
    int sc_commandEncode(int command, int operand, int* value);
    int sc_commandDecode(int* command, int* operand, int value);
};

#endif //ARCHITECT_MYSIMPLECOMPUTER_H
