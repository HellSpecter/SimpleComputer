#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myReadKey.h"



int mainLogic() {
    const char* filename = "new.txt";
    system("touch new.txt");

    mySC obj = mySC();

    obj.sc_memoryInit();
    obj.sc_regInit();

    int currentIndex = 0;
    obj.printAll(currentIndex);

    KEYS key = none;

    while(key != closeApp) {
        obj.printAll(currentIndex);
        rk_readKey(key);
        switch(key) {
            case none:
                break;
            case load:
                obj.sc_memoryLoad(filename);
                break;
            case save:
                obj.sc_memorySave(filename);
                break;
            case run:
                //std::cout << "r";
                break;
            case step:
                //std::cout << "s";
                break;
            case reset:
                //std::cout << "i";
                break;
            case accumulator:
                //std::cout << "F5";
                int value;
                mt_setForeground(YELLOW);

                mt_gotoXY(24, 2);
                std::cout << "Input: ";

                std::cin >> std::hex >> value;
                value &= 0b111111111111111;
                std::cin >> std::dec;
                mt_setForeground(BLUE);
                obj.sc_memorySet(currentIndex, value);
                break;
            case instructionCounter:
                std::cout << "F6";
                break;
            case up:
                if(currentIndex > 9) {
                    currentIndex -= 10;
                }
                break;
            case down:
                if(currentIndex < 90) {
                    currentIndex += 10;
                }
                break;
            case left:
                if(currentIndex % 10 != 0) {
                    currentIndex -= 1;
                }
                break;
            case right:
                if(currentIndex % 10 != 9) {
                    currentIndex += 1;
                }
                break;

            default:
                break;
        }
    }

    return 0;
}

int main() {
    mainLogic();
    return 0;
}