#include "stdafx.h"
#include "SymTab.h"
#include <iomanip>

  std::map<string, int> SymbolTable::m_symbolTable;
/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( char *a_symbol, int a_loc );

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.

Returns

	Returns nothing

Author

	Victor Miller

*/
/**/
void SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record the location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}/* void SymbolTable::AddSymbol( string &a_symbol, int a_loc ) */

/*
NAME

	DisplaySymbolTable - Display the existing symbol table.

SYNOPSIS

	void DisplaySymbolTable( );

DESCRIPTION

	This function displays a header, followed by the existing symbols, 
	location, and number.

Returns

	Returns nothing

Author

	Adam Roberts
*/
/**/
void SymbolTable::DisplaySymbolTable()
{
	cout << setw(12) << left << "Symbol #" << setw(12) << left << "Symbol" << setw(12) << left << "Location" << endl;
	int count = 0;
	for(map<string, int>::iterator st = m_symbolTable.begin(); st != m_symbolTable.end(); ++st) {
		cout << " " << setw(12) << left << count++ << setw(12) << left << st->first << setw(12) << left << st->second << endl;
	}
	cout << "_________________________________________________________________________________\n\n";
	cout << "Press Enter to continue...";
	cin.ignore();
}/* void SymbolTable::DisplaySymbolTable() */

/*
NAME

	LookupSymbol - Search the symbol table for a specific symbol.

SYNOPSIS

	bool LookupSymbol( string a_symbol, int *a_loc )

DESCRIPTION

	This function returns a bool if a symbol exists in the table, 
	adjusting the current location if found.

Returns

	Returns bool

Author

	Adam Roberts

*/
/**/
bool SymbolTable::LookupSymbol(string a_symbol, int &a_loc)
{
	map<string, int>::iterator st = m_symbolTable.find(a_symbol);
	if(st != m_symbolTable.end() ) {
		a_loc = st->second;
		return true;
	}
	return false;
}/* bool SymbolTable::LookupSymbol(string a_symbol, int &a_loc) */
