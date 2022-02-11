#include "mySimpleComputer.h"
#include "myTerm.h"

int main() {
    const char* filename = "new.txt";
    //std::string filename = "memory.txt";
    mySC obj = mySC();

    obj.sc_memoryInit();
    obj.sc_regInit();
    //obj.sc_regSet(OUT_OF_BOUNDS, true);
    //auto* ptr = new unsigned int;
    //obj.sc_regGet(OUT_OF_BOUNDS, ptr);
    //std::cout << "\nTest = " << *ptr << "\n";
    obj.print();

    obj.sc_memorySet(2, 15);
    obj.print();
    // тестим sc_memorySave, sc_memoryLoad
    obj.sc_memorySave(filename);

    obj.sc_memorySet(5, 999);
    obj.sc_memorySet(100, 100);
    obj.print();

    obj.sc_memoryLoad(filename);
    obj.print();

    mt_clearScreen();
    // тестим sc_commandDecode
    std::cout << "\nTESTING sc_commandDecode:\n";
    auto* input = new int;
    *input = 0b001100111011001; // 0b001100111011001 == 33 59
    std::cout << "\nEntered command+operand (decimal): " << *input << "\n";
    auto* decodedCommand = new int;
    auto* decodedOperand = new int;
    obj.sc_commandDecode(decodedCommand, decodedOperand, *input);
    std::cout << "Decoded Command: " << std::hex << *decodedCommand << "\n";
    std::cout << "Decoded Operand: " << *decodedOperand << "\n";
    // тестим sc_commandEncode
    std::cout << "\nTESTING sc_commandEncode:\n";
    auto* output = new int;
    obj.sc_commandEncode(*decodedCommand, *decodedOperand, output);
    std::cout << "\nEncoded command+operand (decimal): " << std::dec << *output << "\n";

    mt_clearScreen();
    obj.print();

    return 0;
}