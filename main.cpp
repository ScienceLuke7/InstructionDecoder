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
    // stores the current instruction into the Instruction Register (IR)
    IR = memory[PC];
    
    // if math opcode
    if ((IR & 0x80) == 0x80) {
    // put math fetching process in here
        PC++;
    }
    // check if memory op
    else if ((IR & 0xF0) == 0x00) {
        // check if store op
        if ((IR & 0x08) == 0x0) {
            // add check for ACC and else for MAR
            if ((IR & 0x04) == 0x0) {
                if ((IR & 0x03) == 0x0) {
                    PC += 3;
                } 
                else {
                    PC++;
                }
            }
            // else MAR
            else {
                if ((IR & 0x03) == 0x0) {
                    PC += 3;
                } 
            }
        }
        // check if load op
        else {
            // add check again for load into ACC and else for MAR
            if((IR & 0x04) == 0x0) {
                if ((IR & 0x03) == 0x0) {
                    PC =+ 3;
                }
                else if ((IR & 0x03) == 0x01) {
                    PC += 2;
                }
                else {
                    PC++;
                }
            }
            // else mar
            else {
                if ((IR & 0x03) == 0x0) {
                    PC =+ 3;
                }
                else if ((IR & 0x03) == 0x01) {
                    PC += 3;
                }
                else {
                    PC++;
                }
            }
        }

    }
    // if branch opcode; applies a bitmask to see if opcode is a valid branch opcode (00010 aka 0x10)
    else if ((IR & 0xF8) == 0x10) {
        // increments PC to skip over the branch operands to the next instruction
        PC += 3;
    } 
    // if special opcode
    else {
        // no opcode condition; stated by project specifications to increment PC by 1 if opcode is 0001_1000 (0x18)
        if (IR == 0x18) {
            PC++;
        }
        // halt opcode requires no check
    }

}

void executeInstruction() {
    // if math opcode
    if ((IR & 0x80) == 0x80) {
    // put math execution process in here
        int opertion;
        int src;
        string dest;
        int mathVar;
        int nextByte = 1;
        
       //finding the destintion
        switch (IR & 0x0C)
        {
        case 0x00:
            /* indirect */
            dest = "IND";
            mathVar = memory[MAR];
            break;
        case 0x01:
            /* Accumulator */
            dest = "ACC";
            mathVar = ACC;
            break;
        case 0x02:
            /* Register MAR */
            dest = "MAR";
            mathVar = MAR;
            break;
        case 0x03:
            /* memory */
            dest = "MEM";
            mathVar = memory[PC + nextByte];
            nextByte++;
            break;
        
        default:
            break;
        }
     //finding the src
        switch (IR & 0x03)
        {
        case 0x00:
            /* indirect */
            src = memory[MAR];
            break;
        case 0x01:
            /* Accumulator */
            src = ACC;
            break;
        case 0x02:
            /* Constant */
            src = memory[PC + nextByte];
            break;
        case 0x03:
            /* Memory */
            src = memory[memory[PC + nextByte]];
            break;
        
        default:
            break;
        }


        switch ((IR & 0x70))
        {
        case 0x00:
            /* AND */
            if (dest == "IND"){
                memory[MAR] = src & mathVar;
            }else if (dest == "ACC") {
                ACC = src & mathVar;
            }else if (dest == "MAR"){
                MAR = src & mathVar;
            }else if (dest == "MEM"){
                memory[PC] = src & mathVar;
            }
            break;
        case 0x10:
            /* OR */
            if (dest == "IND"){
                memory[MAR] = src | mathVar;
            }else if (dest == "ACC") {
                ACC = src | mathVar;
            }else if (dest == "MAR"){
                MAR = src | mathVar;
            }else if (dest == "MEM"){
                memory[PC] = src | mathVar;
            }
            break;
        case 0x20:
            /* XOR */
             if (dest == "IND"){
                memory[MAR] = src ^ mathVar;
            }else if (dest == "ACC") {
                ACC = src ^ mathVar;
            }else if (dest == "MAR"){
                MAR = src ^ mathVar;
            }else if (dest == "MEM"){
                memory[PC] = src ^ mathVar;
            }
            break;
        case 0x30:
            /* ADD */
             if (dest == "IND"){
                memory[MAR] = src + mathVar;
            }else if (dest == "ACC") {
                ACC = src + mathVar;
            }else if (dest == "MAR"){
                MAR = src + mathVar;
            }else if (dest == "MEM"){
                memory[PC] = src + mathVar;
            }
            break;
        case 0x40:
            /* SUB */
             if (dest == "IND"){
                memory[MAR] = src - mathVar;
            }else if (dest == "ACC") {
                ACC = src - mathVar;
            }else if (dest == "MAR"){
                MAR = src - mathVar;
            }else if (dest == "MEM"){
                memory[PC] = src - mathVar;
            }
            break;
        case 0x50:
            /* INC */
             if (dest == "IND"){
                memory[MAR] = src++;
            }else if (dest == "ACC") {
                ACC = src++;
            }else if (dest == "MAR"){
                MAR = src++;
            }else if (dest == "MEM"){
                memory[PC] = src++;
            }
            break;
        case 0x60:
            /* DEC */
            if (dest == "IND"){
                memory[MAR] = src--;
            }else if (dest == "ACC") {
                ACC = src--;
            }else if (dest == "MAR"){
                MAR = src--;
            }else if (dest == "MEM"){
                memory[PC] = src--;
            }
            break;
        case 0x70:
            /* NOT */
            if (dest == "IND"){
                memory[MAR] = ~src;
            }else if (dest == "ACC") {
                ACC = ~src;
            }else if (dest == "MAR"){
                MAR = ~src;
            }else if (dest == "MEM"){
                memory[PC] = ~src;
            }
            break;    
        default:
            break;
        }

    }
    // check is memory op
    else if ((IR & 0xF0) == 0x00) {
        //memory ops vars
        string valMethod;
        string memTracker;
        
        switch ((IR & 0x0F)) 
        {
        case 0x00:
            valMethod = memory[memory[PC]];
            memTracker = "mm";
            break;
        
        case 0x01:
            valMethod = memory[PC - 1];
            memTracker = "m";
            break;
        case 0x02:
            valMethod = memory[MAR];
            memTracker = "mmar";
            break;
        default:
            break;
        }

        
        switch ((IR & 0xF0))
        {
        case 0x00:      //0000 Store ACC
            memory[(memory[PC - 2] << 8) + memory[PC - 1]] = ACC; 
            break;

        case 0x40:      //0100 Store MAR
            memory[(memory[PC - 2] << 8) + memory[PC - 1]] = (MAR & 0xFF00) >> 8;
            break;

        case 0x80:      //1000 Load ACC
            ACC = memory[(memory[PC - 2] << 8) + memory[PC - 1]];
            break;

        case 0xC0:      //1100  Load MAR
            if(memTracker == "mm"){

                MAR += (memory[(memory[PC - 2] << 8) + memory[PC - 1] + 1]);
            }else if (memTracker == "m")
            {
                MAR = (memory[(memory[PC - 2] << 8) + memory[PC - 1]]) << 8;
            }else if (memTracker == "mmar")
            {
                MAR = memory[MAR];
            }
            break;    
        default:
            break;
        }
/*
        switch ((IR & 0xF0))
        {
        case 0x00:      //0000 Store ACC
            memory[(memory[PC - 2] << 8) + memory[PC - 1]] = ACC;
            break;

        case 0x40:      //0100 Store MAR
            memory[(memory[PC - 2] << 8) + memory[PC - 1]] = (MAR & 0xFF00) >> 8;
            break;

        case 0x80:      //1000 Load ACC
            // if ACC is destination and method is operand address (1000)
            ACC = memory[(memory[PC - 2] << 8) + memory[PC - 1]];
            break;

        case 0xC0:      //1100  Load MAR
            MAR = (memory[(memory[PC - 2] << 8) + memory[PC - 1]]) << 8;
            MAR += (memory[(memory[PC - 2] << 8) + memory[PC - 1] + 1]);
            break;    
        default:
            break;
        }

*/


    }
    // if branch opcode; applies same branching bitmask here to see if opcode is a valid branch opcode (00010 aka 0x10)
    else if ((IR & 0xF8) == 0x10) {
        // determines which branching should occur based on the last three bits of the opcode (0000_0111 aka 0x07)
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



