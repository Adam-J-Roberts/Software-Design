//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler {

public:
	Assembler(int argc, char* argv[]) : m_facc(argc, argv) {};		//Constructor for Assembler class
    
	void PassI( );													// Pass I - establish the locations of the symbols
	void PassII( );													// Pass II - generate a translation
	void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }    // Display the symbols in the symbol table.
    void RunProgramInEmulator();									// Run emulator on the translation.

private:

	FileAccess m_facc;												// File Access object
    SymbolTable m_symtab;											// Symbol table object
    Instruction m_inst;												// Instruction object
    emulator m_emul;												// Emulator object
	vector<pair<int, string>> m_code;								// Machine code 							
};

