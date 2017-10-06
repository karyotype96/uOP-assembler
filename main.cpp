/**
    REFERENCE:

    FUNCTION CODES

    NOP     - 0     - No operation
    LDA     - 1     - Load register A
    LDB     - 2     - Load register B
    LDS     - 3     - Load register S
    LDMAR   - 4     - Load memory address register (MAR)
    STOI    - 5     - Store operand in RAM at address MAR
    STOR    - 6     - Store register in RAM at address MAR
    RDR     - 7     - Read from RAM at address MAR
    JMP     - 8     - Unconditional jump
    JNZ     - 9     - Jump if R is not zero

    REGISTERS

    A       - 0     - ALU operand / general purpose register
    B       - 1     - ALU operand / general purpose register
    S       - 2     - ALU operator
    MAR     - 3     - RAM address
    R       - 4     - ALU result (read-only)
    PC      - 5     - Program counter

    OPERATIONS

    ADD     - 0
    SUB     - 1
    AND     - 2
    OR      - 3
    XOR     - 4

*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Parser.h"

int main()
{
    std::vector<OPCODE> opcodes;
    std::string buffer;
    std::string outputFilename;

    std::string outputString;

    int lineNum = 0;

    std::ifstream inputfile;
    inputfile.open("source.lg", std::fstream::out | std::fstream::in | std::fstream::app);

    if (inputfile.is_open()){
        while (true){
            inputfile >> buffer;
            opcodes.push_back(Parser::parse(buffer, lineNum));
            lineNum++;
            if (inputfile.eof()) break;
        }
    }

    std::cout << "Assembled program: ";
    for (int i = 0; i < opcodes.size(); i++){
        std::cout << std::hex << opcodes[i].operand << opcodes[i].funccode << " ";
    }
    std::cout << std::endl;

    return 0;
}
