#include "mySimpleComputer.h"

mySC::mySC() {
    this->sc_regInit();
    this->sc_memoryInit();
}

void mySC::print() {
    // рамка сверху
    std::cout << "┌";
    for (int i = 0; i < 10; i++) {
        std::cout << "──────";
        if (i == 3) {
            std::cout << "Memory";
            i += 1;
        }
    }
    std::cout << "─┐\n│ ";
    // вывод цифр из памяти
    for(int i = 0; i < SIZE; i++) {
        if((i % 10 == 0) && (i != 0)) {
            std::cout << "│\n│ ";
        }

        std::cout << '+' << std::setw(4) << std::setfill('0') << ram[i] << ' ';
    }
    // рамка снизу
    std::cout << "│\n└";
    for(int i = 0; i < 10; i++) {
        std::cout << "──────";
    }
    std::cout << "─┘\n";

    // вывод флагов
    std::cout << "Names: O Z B C I\n";
    std::cout << "Flags: " << ((flags >> OPERATION_OVERFLOW) & 0x1) << " "
                      << ((flags >> DIVISION_BY_ZERO) & 0x1) << " "
                      << ((flags >> OUT_OF_BOUNDS) & 0x1) << " "
                      << ((flags >> CLOCK_PULSE_IGNORE) & 0x1) << " "
                      << ((flags >> INVALID_COMMAND) & 0x1) << " ";
    std::cout << "\n\n";
}

int mySC::sc_memoryInit() {
    std::fill(ram, ram + SIZE, 0);
    return 0;
}

int mySC::sc_memorySet(int address, int value) {
    if ((address < 0) || (address >= SIZE)) {
        //cout << "\nустанавливается флаг «выход за границы памяти»\n";
        this->sc_regSet(OUT_OF_BOUNDS, true);
        return 1;
    }
    ram[address] = value;
    return 0;
}

int mySC::sc_memoryGet(int address, int* value) {
    if ((address < 0) || (address >= SIZE)) {
        //cout << "\nустанавливается флаг «выход за границы памяти»\n";
        this->sc_regSet(OUT_OF_BOUNDS, true);
        return 1;
    }
    *value = ram[address];
    return 0;
}

int mySC::sc_memorySave(const char* filename) {
    //FILE* ptrFile = fopen(filename, "wb");
    //fwrite(ram, sizeof(int), SIZE, ptrFile);
    //fclose(ptrFile);
    //std::ofstream outfile("memory.txt", std::ofstream::binary);
    //outfile.write(ram, sizeof(int) * SIZE);
    //std::string command = "touch ";
    //printf(command,"touch %s", filename); sprintf("touch ", "%s", filename)
    //system(command);
    int fileDescriptor = open(filename, O_WRONLY);
    write(fileDescriptor, ram, sizeof(int) * SIZE);
    close(fileDescriptor);
    return 0;
}

int mySC::sc_memoryLoad(const char* filename) {
    //FILE* ptrFile = fopen(filename, "rb");
    //fread(ram, sizeof(int), SIZE, ptrFile);
    //fclose(ptrFile);
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
            //std::cout << "\nфлаг неверная команда\n";
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
            //std::cout << "\nфлаг неверная команда\n";
            return -1;
        }
    }
    else {
        this->sc_regSet(INVALID_COMMAND, true);
        //std::cout << "\nфлаг неверная команда\n";
        return -1;
    }
}

