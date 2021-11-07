#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define HALT_OPCODE 0x19

void fetchNextInstruction(void);
void executeInstruction(void);
void readFileIntoMem(unsigned char* memory);

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

void fetchNextInstruction() {
    
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
    /* else if (stuff) {

    } 
    // if special opcode
    else {

    }*/

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
    /* else if (stuff) {

    }
    // if special opcode
    else {

    } */
}