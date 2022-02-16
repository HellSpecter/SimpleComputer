#include "mySimpleComputer.h"
#include "myTerm.h"

int main() {
    const char* filename = "new.txt";
    system("touch new.txt");

    mySC obj = mySC();

    obj.sc_memoryInit();
    obj.sc_regInit();

    obj.printAll();

    return 0;
}