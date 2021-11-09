#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define HALT_OPCODE 0x19

void fetchNextInstruction(void);
void executeInstruction(void);
void readFileIntoMem(unsigned char* memory);
void writeToOutputFile(unsigned char* memory);

unsigned char memory[65536];
unsigned char ACC = 0;
unsigned char IR = 0;
unsigned int MAR = 0;
unsigned int PC = 0;


int main(int argc, char* argv[]) {

    readFileIntoMem(memory);
    while(memory[PC] != HALT_OPCODE) {
        fetchNextInstruction();
        executeInstruction();
    }

    writeToOutputFile(memory);
    return 0;

}

void readFileIntoMem(unsigned char* memory) {
    ifstream memFile("mem_in.txt");
    string lineString;
    char charBuffer[2];
    // reads each line of the file; delimits by spaces
    while(getline(memFile, lineString, ' ')) {
        // copies each memory data into a character buffer
        lineString.copy(charBuffer, 2);
        // assigns each memory data chararcter pair to the memory var
        *memory = (unsigned char)strtoul(charBuffer, NULL, 16);
        memory++;
        
    }

    memFile.close();
}

void writeToOutputFile(unsigned char* memory) {
    ofstream oMemFile("mem_out.txt");
    oMemFile.clear();
    int i = 0;
    while (memory[i] != HALT_OPCODE) {
        if (i % 10 == 0 && i != 0) {
            oMemFile << '\n';
        }
        oMemFile << memory[i] + ' ';
        i++;
    }

    oMemFile.close();
}


void fetchNextInstruction() {
    IR = memory[PC];
    
    // if math opcode
    if (false) {
    // put math fetching process in here

    }
    // if memory opcode
    else if (false) {
    // put memory fetching process in here

    }
    // if branch opcode
    // Chris's stuff
    else if ((IR & 0xF8) == 0x10) {
        PC += 3;
    } 
    // if special opcode
    else {
        // no opcode condition
        if (IR == 0x18) {
            PC++;
        }
        // halt opcode requires no check
    }

}

void executeInstruction() {

    // if math opcode
    if (false) {
    // put math execution process in here

    }
    // if memory opcode
    else if (false) {
    // put memory execution process in here

    }
    // if branch opcode
    // Chris's stuff
    else if ((IR & 0xF8) == 0x10) {
        switch ((IR & 0x07))
        {
        case 0x00:
            // obtains a 16 bit address and stores in PC
            PC = (memory[PC - 2] << 8) + memory[PC - 1];
            break;
        case 0x01:
            PC = ACC == 0 ? (memory[PC - 2] << 8) + memory[PC - 1] : PC;
            break;
        case 0x02:
            PC = ACC != 0 ? (memory[PC - 2] << 8) + memory[PC - 1] : PC;
            break;
        case 0x03:
            PC = ACC < 0 ? (memory[PC - 2] << 8) + memory[PC - 1] : PC;
            break;
        case 0x04:
            PC = ACC <= 0 ? (memory[PC - 2] << 8) + memory[PC - 1] : PC;
            break;
        case 0x05:
            PC = ACC > 0 ? (memory[PC - 2] << 8) + memory[PC - 1] : PC;
            break;
        case 0x06:
            PC = ACC >= 0 ? (memory[PC - 2] << 8) + memory[PC - 1] : PC;
            break;        
        default:
            break;
        }
    }
    // if special opcode
    else {
        // do nothing
    }
}