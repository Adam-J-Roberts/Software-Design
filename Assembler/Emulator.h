//
//		Emulator class - supports the emulation of Duck2200 programs
//
#ifndef _EMULATOR_H  
#define _EMULATOR_H

class emulator {

public:
	
	emulator() {											//Constructor of the Emulator class setting the memory size
		memset( m_memory, 0, MEMSZ * sizeof(int) ); 
	}	
    const static int MEMSZ = 100'000;						// The size of the memory of the Duck2200.

    bool insertMemory( int a_location, int a_contents );    // Records instructions and data into Duck2200 memory.
    bool runProgram( );										// Runs the Duck2200 program recorded in memory.
	
private:

    int m_memory[MEMSZ];									// The memory of the Duck2200.
    int accumulator;										// The accumulator for the Duck2200
	int m_loc;												// Store the current location
	int m_opcode;											// Store the opcode for the current statement
	int m_operand;											// Store the operand for the current statement

	void add();												// Performs the addition function of the language.
	void sub();												// Performs the subtraction function of the language.
	void mult();											// Performs the multiplication function of the language.
	void div();												// Performs the division function of the language.
	void load();											// Performs the loading function of the language.
	void store();											// Performs the store function of the language.
	void read();											// Performs the read function of the language.
	void write();											// Performs the write function of the language.
	void b();												// Performs a relocation function of the language.
	void bm();												// Performs a relocation function of the language.
	void bz();												// Performs a relocation function of the language.
	void bp();												// Performs a relocation function of the language.
	
};

#endif

