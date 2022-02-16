#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"

mySC::mySC() {
    this->sc_regInit();
    this->sc_memoryInit();
}

int mySC::printAll() {
    mt_clearScreen();

    mt_setForeground(LIGHT_BLUE);
    std::cout << std::hex;
    mt_gotoXY(2, 2);
    for(int i = 0; i < SIZE; i++) {
        if((i % 10 == 0) && (i != 0)) {
            std::cout << "\n ";
        }
        std::cout << '+' << std::setw(4) << std::setfill('0') << ram[i] << ' ';
    }
    std::cout << std::dec;
    bc_box(1, 1, 10 * 6, 10);

    bc_box(1, 63, 20, 1);
    bc_box(4, 63, 20, 1);
    bc_box(7, 63, 20, 1);

    // flags
    mt_gotoXY(11, 69);
    ((flags >> OPERATION_OVERFLOW) & 0x1) == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "O ";
    ((flags >> DIVISION_BY_ZERO) & 0x1) == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "Z ";
    ((flags >> OUT_OF_BOUNDS) & 0x1) == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "B ";
    ((flags >> CLOCK_PULSE_IGNORE) & 0x1) == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "C ";
    ((flags >> INVALID_COMMAND) & 0x1) == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "I ";
    mt_setForeground(WHITE);
    bc_box(10, 63, 20, 1);

    // big chars
    bc_box(13, 1, 45, 8);
    bc_printBigChar(PLUS, 14, 2, BLACK, LIGHT_BLUE);
    bc_printBigChar(ZERO, 14, 11, BLACK, LIGHT_BLUE);
    bc_printBigChar(ZERO, 14, 20, BLACK, LIGHT_BLUE);
    bc_printBigChar(ZERO, 14, 29, BLACK, LIGHT_BLUE);
    bc_printBigChar(ZERO, 14, 38, BLACK, LIGHT_BLUE);

    // info
    mt_setForeground(LIGHT_BLUE);
    mt_gotoXY(14, 50);
    std::cout << "l == load";
    mt_gotoXY(15, 50);
    std::cout << "s == save";
    mt_gotoXY(16, 50);
    std::cout << "r == run";
    mt_gotoXY(17, 50);
    std::cout << "t == step";
    mt_gotoXY(18, 50);
    std::cout << "i == reset";
    mt_gotoXY(19, 50);
    std::cout << "F5 == accumulator";
    mt_gotoXY(20, 50);
    std::cout << "F6 == instructionCounter";
    bc_box(13, 48, 35, 8);

    // names
    mt_setForeground(BLUE);
    mt_gotoXY(1, 25);
    std::cout << " Memory ";
    mt_gotoXY(1, 67);
    std::cout << " Accumulator ";
    mt_gotoXY(4, 64);
    std::cout << " instructionCounter ";
    mt_gotoXY(7, 68);
    std::cout << " Operation ";
    mt_gotoXY(10, 70);
    std::cout << " Flags ";
    mt_gotoXY(13, 60);
    std::cout << " Keyboard ";

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    return 0;
}

int mySC::sc_memoryInit() {
    std::fill(ram, ram + SIZE, 0);
    return 0;
}

int mySC::sc_memorySet(int address, int value) {
    if ((address < 0) || (address >= SIZE)) {
        this->sc_regSet(OUT_OF_BOUNDS, true);
        return 1;
    }
    ram[address] = value;
    return 0;
}

int mySC::sc_memoryGet(int address, int* value) {
    if ((address < 0) || (address >= SIZE)) {
        this->sc_regSet(OUT_OF_BOUNDS, true);
        return 1;
    }
    *value = ram[address];
    return 0;
}

int mySC::sc_memorySave(const char* filename) {
    int fileDescriptor = open(filename, O_WRONLY);
    write(fileDescriptor, ram, sizeof(int) * SIZE);
    close(fileDescriptor);
    return 0;
}

int mySC::sc_memoryLoad(const char* filename) {
    int fileDescriptor = open(filename, O_RDONLY);
    read(fileDescriptor, ram, sizeof(int) * SIZE);
    close(fileDescriptor);
    return 0;
}

int mySC::sc_regInit() {
    flags = 0;
    return 0;
}
/* flags = (flags | (1 << CLOCK_PULSE_IGNORE));
     * flags |= (1 << CLOCK_PULSE_IGNORE);
     * этой строкой мы устанавливаем
     * флаг 4 разряда (слева направо начиная с 1)
    */
int mySC::sc_regSet(int flagName, bool value) {
    if ((flagName > 5) || (flagName < 1)) {
        return -1;
    }
    if(value) {
        flags |= (1 << flagName);
    } else {
        flags &= (~(1 << flagName));
    }
    return 0;
}

int mySC::sc_regGet(int flagName, unsigned int* value) {
    if ((flagName > 5) || (flagName < 1)) {
        return -1;
    }
    *value = ((flags >> flagName) & 0x1);
    return 0;
}

int mySC::sc_commandEncode(int command, int operand, int* value) {
    if(operand <= 0x7F) {
        if (std::binary_search(std::begin(COMMANDS), std::end(COMMANDS), command)) {
            *value = (command << 7) | operand;
            return 0;
        } else {
            this->sc_regSet(INVALID_COMMAND, true);
            return -1;
        }
    } else {
        return -1;
    }
}

int mySC::sc_commandDecode(int* command, int* operand, int value) {
    int tempCommand;

    if (((value >> 14) & 1) == 0) {
        tempCommand = value >> 7;
        if (std::binary_search(std::begin(COMMANDS), std::end(COMMANDS), tempCommand)) {
            *command = tempCommand;
            *operand = value & 0x7F;
            return 0;
        } else {
            this->sc_regSet(INVALID_COMMAND, true);
            return -1;
        }
    }
    else {
        this->sc_regSet(INVALID_COMMAND, true);
        return -1;
    }
}

