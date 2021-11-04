#define HALT_OPCODE 0x19

void fetchNextInstruction(void);
void executeInstruction(void);

unsigned char memory[65536];
unsigned char ACC = 0;
unsigned char IR = 0;
unsigned int MAR = 0;
unsigned int PC = 0;


int main(int argc, char* argv[]) {

    while(memory[PC] != HALT_OPCODE) {
        fetchNextInstruction();
        executeInstruction();
    }
    return 0;

}

void fetchNextInstruction() {
    // put individual fetching process in here
}

void executeInstruction() {
    // put individual execution process in here
}