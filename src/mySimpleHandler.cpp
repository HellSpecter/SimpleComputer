#include "mySimpleHandler.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadKey.h"

struct Handler {
    int accumulator = 0;
    int instructionCounter = 0;
    int currentIndex = 0;
    mySC computer;
};

Handler myHandler;

void sh_reset() {
    //mainLogic();
    myHandler.computer.sc_memoryInit();
    myHandler.computer.sc_regInit();

    myHandler.computer.sc_regSet(CLOCK_PULSE_IGNORE, true);

    myHandler.instructionCounter = 0;
    myHandler.currentIndex = 0;
    printAll();

    KEYS key = none;
}

void sh_run() {
    myHandler.computer.sc_regSet(CLOCK_PULSE_IGNORE, false);
    KEYS key = none;
    //signal(SIGALRM, signalHandler);                ///////////////signal_handler
    unsigned int tempFlag, tempFlag1;
    myHandler.computer.sc_regGet(CLOCK_PULSE_IGNORE, &tempFlag);
    myHandler.computer.sc_regGet(OUT_OF_BOUNDS, &tempFlag1);
    while(tempFlag == 0 && tempFlag1 == 0) {
        mt_clearScreen();
        printAll();
        myHandler.currentIndex = myHandler.instructionCounter;

        pause();
        rk_readKey(key);

        printAll();
        if(myHandler.instructionCounter >= 99 || key == KEYS::reset) {
            //sh_reset();

            raise(SIGUSR1);
            break;
            //myHandler.computer.sc_regSet(CLOCK_PULSE_IGNORE, true);
        }
        myHandler.computer.sc_regGet(CLOCK_PULSE_IGNORE, &tempFlag);
        myHandler.computer.sc_regGet(OUT_OF_BOUNDS, &tempFlag1);
        fflush(stdout);
    }

}

void setTimer(long interval) {
    itimerval nval, oval;

    nval.it_interval.tv_sec = interval;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &nval, &oval);
}

void signalReset(int signal) {
    sh_reset();
    //myHandler.computer.sc_regSet(CLOCK_PULSE_IGNORE, true);
}

void signalHandler(int signal) {
    unsigned int value, value1;
    myHandler.computer.sc_regGet(CLOCK_PULSE_IGNORE, &value);
    myHandler.computer.sc_regGet(OUT_OF_BOUNDS, &value1);
    if(value == 0 && value1 == 0) {
        myHandler.instructionCounter++;
        myHandler.currentIndex = myHandler.instructionCounter;
        mt_clearScreen();
        printAll();
    } else if (value1 == 1){
        sh_reset();
        printAll();
    }
}

int printAll() {
    mt_clearScreen();

    mt_setForeground(LIGHT_BLUE);
    std::cout << std::hex;
    mt_gotoXY(2, 2);
    for(int i = 0; i < 100; i++) {
        int currentValue;
        myHandler.computer.sc_memoryGet(i, &currentValue);
        if((i % 10 == 0) && (i != 0)) {
            std::cout << "\n ";
        }
        if(i == myHandler.currentIndex) {
            mt_setForeground(YELLOW);
        }
        if (((currentValue >> 14) & 1) == 0)
            std::cout << '+';
        else
            std::cout << '-';
        std::cout << std::setw(4) << std::setfill('0') << currentValue << ' ';
        mt_setForeground(LIGHT_BLUE);
    }
    std::cout << std::dec;
    bc_box(1, 1, 10 * 6, 10);

    bc_box(1, 63, 20, 1);
    bc_box(4, 63, 20, 1);
    bc_box(7, 63, 20, 1);

    // flags
    mt_gotoXY(11, 69);
    unsigned int tempFlag;
    myHandler.computer.sc_regGet(OPERATION_OVERFLOW, &tempFlag);
    tempFlag == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "O ";
    myHandler.computer.sc_regGet(DIVISION_BY_ZERO, &tempFlag);
    tempFlag == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "Z ";
    myHandler.computer.sc_regGet(OUT_OF_BOUNDS, &tempFlag);
    tempFlag == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "B ";
    myHandler.computer.sc_regGet(CLOCK_PULSE_IGNORE, &tempFlag);
    tempFlag == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
    std::cout << "C ";
    myHandler.computer.sc_regGet(INVALID_COMMAND, &tempFlag);
    tempFlag == 1 ? mt_setForeground(RED) : mt_setForeground(GREEN);
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
    int valueToPrint = 0;
    myHandler.computer.sc_memoryGet(myHandler.instructionCounter, &valueToPrint);
    if (((valueToPrint >> 14) & 1) == 0)
        bc_printBigChar(PLUS, 14, 2, BLACK, LIGHT_BLUE);
    else
        bc_printBigChar(MINUS, 14, 2, BLACK, LIGHT_BLUE);
    bc_printBigChar((BIGCHARS)((valueToPrint >> 12 ) & 0b1111), 14, 11, BLACK, LIGHT_BLUE);
    //valueToPrint %= 1000;
    bc_printBigChar((BIGCHARS)((valueToPrint >> 8 ) & 0b1111), 14, 20, BLACK, LIGHT_BLUE);
    //valueToPrint %= 100;
    bc_printBigChar((BIGCHARS)((valueToPrint >> 4 ) & 0b1111), 14, 29, BLACK, LIGHT_BLUE);
    //valueToPrint %= 10;
    bc_printBigChar((BIGCHARS)((valueToPrint) & 0b1111), 14, 38, BLACK, LIGHT_BLUE);


    // info
    mt_setForeground(LIGHT_BLUE);
    mt_gotoXY(14, 50);
    std::cout << "l  == load";
    mt_gotoXY(15, 50);
    std::cout << "s  == save";
    mt_gotoXY(16, 50);
    std::cout << "r  == run";
    mt_gotoXY(17, 50);
    std::cout << "t  == step";
    mt_gotoXY(18, 50);
    std::cout << "i  == reset";
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
    // accumulator
    std::cout << " Accumulator ";
    mt_gotoXY(2, 71);
    mt_setForeground(LIGHT_BLUE);
    myHandler.computer.sc_memoryGet(myHandler.currentIndex, &myHandler.accumulator);
    if (((myHandler.accumulator >> 14) & 1) == 0)
        std::cout << '+';
    else
        std::cout << '-';
    std::cout << std::hex << std::setw(4) << std::setfill('0') << myHandler.accumulator << std::dec;
    mt_setForeground(BLUE);
    // instructionCounter
    mt_gotoXY(4, 64);
    std::cout << " instructionCounter ";
    mt_gotoXY(5, 71);
    mt_setForeground(LIGHT_BLUE);
    std::cout << '+' << std::dec << std::setw(4) << std::setfill('0') << myHandler.instructionCounter << std::dec;
    mt_setForeground(BLUE);
    mt_gotoXY(7, 68);
    std::cout << " Operation ";
    mt_gotoXY(10, 70);
    std::cout << " Flags ";
    mt_gotoXY(13, 60);
    std::cout << " Keyboard ";

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    mt_gotoXY(24, 1);
    return 0;
}

int mainLogic() {
    const char* filename = "new.txt";
    system("touch new.txt");

    //computer = new mySC();

    myHandler.computer.sc_memoryInit();
    myHandler.computer.sc_regInit();

    myHandler.computer.sc_regSet(CLOCK_PULSE_IGNORE, true);

    myHandler.instructionCounter = 0;
    //int currentIndex = 0;
    printAll();
    signal(SIGALRM, signalHandler);
    signal(SIGUSR1, signalReset);
    KEYS key = none;

    unsigned int tempFlag;
    myHandler.computer.sc_regGet(CLOCK_PULSE_IGNORE, &tempFlag);

    while(key != closeApp && tempFlag == 1) {
        //signal(SIGALRM, interruptHandler);
        //alarm(1);
        //obj.instructionCounter = counter;
        printAll();
        rk_readKey(key);
        switch(key) {
            case KEYS::none:
                printAll();
                break;
            case KEYS::load:
                myHandler.computer.sc_memoryLoad(filename);
                break;
            case KEYS::save:
                myHandler.computer.sc_memorySave(filename);
                break;
            case KEYS::run:
                sh_run();
                break;
            case KEYS::step:
                //std::cout << "s";
                break;
            case KEYS::reset:
                sh_reset();
                break;
            case KEYS::accumulator:
                //std::cout << "F5";
                int value;
                mt_setForeground(YELLOW);

                mt_gotoXY(24, 2);
                std::cout << "Input: ";

                std::cin >> std::hex >> value;
                value &= 0b111111111111111;
                std::cin >> std::dec;
                mt_setForeground(BLUE);
                myHandler.computer.sc_memorySet(myHandler.currentIndex, value);
                break;
            case KEYS::instructionCounter:
                std::cout << "F6";
                break;
            case KEYS::up:
                if(myHandler.currentIndex > 9) {
                    myHandler.currentIndex -= 10;
                }
                break;
            case KEYS::down:
                if(myHandler.currentIndex < 90) {
                    myHandler.currentIndex += 10;
                }
                break;
            case KEYS::left:
                if(myHandler.currentIndex % 10 != 0) {
                    myHandler.currentIndex -= 1;
                }
                break;
            case KEYS::right:
                if(myHandler.currentIndex % 10 != 9) {
                    myHandler.currentIndex += 1;
                }
                break;

            default:
                //computer.instructionCounter = counter;
                printAll();
                break;
        }
        //obj.instructionCounter = counter;
        printAll();
    }


    return 0;
}