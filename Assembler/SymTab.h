//
//		Symbol table class.
//
#pragma once

class SymbolTable {

public:
    
    const int multiplyDefinedSymbol = -999;							// Default output if symbol defined more than once.

    void AddSymbol( string &a_symbol, int a_loc );					// Add a new symbol to the symbol table.
    void DisplaySymbolTable( );										// Display the symbol table.
	static bool LookupSymbol(string a_symbol, int &a_loc);			// Lookup a symbol in the symbol table.

private:

	static map<string, int> m_symbolTable;							// Map holding symbol table in symbol loc pair

};
