#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

typedef struct oc {
    int operand;
    int funccode;
} OPCODE;

namespace Parser {
    std::string genParsable(std::string str){
        std::string toOut = str;
        if (toOut.empty()){
            return toOut;
        }
        toOut.erase(std::remove(toOut.begin(), toOut.end(), ' '), toOut.end());

        if (toOut == "NOP"){
            toOut.append(":0");
        }

        for (unsigned int i = 0; i < toOut.length(); i++){
            std::toupper(toOut[i]);
        }

        return toOut;
    }

    int operandToInt(std::string str){
        int x;
        std::stringstream s;
        s << std::hex << str;
        s >> x;
        return x;
    }

    int registerToInt(std::string reg){
        int x;
        if (reg == "A"){
            x = 0x0;
        } else if (reg == "B"){
            x = 0x1;
        } else if (reg == "S"){
            x = 0x2;
        } else if (reg == "MAR"){
            x = 0x3;
        } else if (reg == "R"){
            x = 0x4;
        } else if (reg == "PC"){
            x = 0x5;
        } else {
            std::cout << "Invalid register" << std::endl;
            exit(-1);
        }
        return x;
    }

    int ALUToInt(std::string code){
        int x;
        if (code == "ADD"){
            x = 0x0;
        } else if (code == "SUB"){
            x = 0x1;
        } else if (code == "AND"){
            x = 0x2;
        } else if (code == "OR"){
            x = 0x3;
        } else if (code == "XOR"){
            x = 0x4;
        } else {
            std::cout << "Invalid operation" << std::endl;
            exit(-1);
        }
        return x;
    }

    OPCODE parse(std::string str){
        OPCODE o;
        std::string toParse = genParsable(str);
        std::string operand, code;

        for (unsigned int i = 0; i < toParse.length(); i++){
            if (toParse.at(i) == ':'){
                code = toParse.substr(0, i);
                break;
            }
        }

        for (unsigned int i = toParse.length() - 1; i > 0; i--){
            if (toParse.at(i) == ':'){
                operand = toParse.substr(i + 1, toParse.length() - i);
                break;
            }
        }

        //big ol' box full of if else statements because switch statements only work on integers.
        //go figure.
        if (code == "NOP"){
            o.funccode = 0;
            o.operand = 0;
        } else if (code == "LDA"){
            o.funccode = 1;
            o.operand = operandToInt(operand);
        } else if (code == "LDB"){
            o.funccode = 2;
            o.operand = operandToInt(operand);
        } else if (code == "LDS"){
            o.funccode = 3;
            o.operand = ALUToInt(operand);
        } else if (code == "LDMAR"){
            o.funccode = 4;
            o.operand = operandToInt(operand);
        } else if (code == "STOI"){
            o.funccode = 5;
            o.operand = operandToInt(operand);
        } else if (code == "STOR"){
            o.funccode = 6;
            o.operand = registerToInt(operand);
        } else if (code == "RDR"){
            o.funccode = 7;
            o.operand = registerToInt(operand);
        } else if (code == "JMP"){
            o.funccode = 8;
            o.operand = operandToInt(operand);
        } else if (code == "JNZ"){
            o.funccode = 9;
            o.operand = operandToInt(operand);
        } else {
            exit(-1);
        }

        return o;

    }
}

#endif // PARSER_H
