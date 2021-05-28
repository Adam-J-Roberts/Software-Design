#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "Instruction.h"
#include "FileAccess.h"
#include <iomanip>
#include <iostream>

/*
NAME

	PassI - places symbols and locations into symbol table.

SYNOPSIS

	void PassI( );

DESCRIPTION

	This function will place the symbol "a_symbol" and its location "a_loc"
	in the symbol table.

Returns
	
	Returns nothing

Author
	
	Adam Roberts

*/
/**/
void Assembler::PassI()
{
	int loc = 0;        // Tracks the location of the instructions to be generated.

	// Successively process each line of source code.
	for (; ; ) {

		// Read the next line from the source file.
		string line;
		if (!m_facc.GetNextLine(line)) {

			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(line);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}
		// If the instruction has a label, record it and its location in the
		// symbol table.
		if (m_inst.isLabel()) {

			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}/*void Assembler::PassI( );*/

/*
NAME

	PassII - generates machine code out of the existing source code.

SYNOPSIS

	void PassII( );

DESCRIPTION

	This function takes the existing source code and translates it into 
	a machine code, that is then stored into a map of location and translation.
	The information is all displayed.

Returns
	
	Returns nothing

Author
	
	Adam Roberts

*/
/**/
void Assembler::PassII()
{
	m_facc.rewind();																				//Reset file 
	int loc = 0;																					//Reset location
	bool eoi = false;																				//End of Instructions Flag
	string buff;																					//Temp string for command lines
	Errors::InitErrorReporting();																	//Initiate error reporting
	pair<int, string>  translation;																	//Translated statement

	cout << setw(12) << left << "Location" << setw(12) << left << "Contents"						//Display PassII menu
		<< "Original Statement" << endl;
	
	for( ; ; ){																						//Loop through code till eoi==true
		buff.clear();																				//Clear temp string
		
		if(!m_facc.GetNextLine(buff)) {																//Check for next line and loading into temp
			if(eoi == true){ break; }
			else {																					//Check for eoi and no end statement, report error
				string error = "(Location: " + to_string(loc) + ") Missing end statement";
				Errors::RecordError(error);
				break;
			}
		}
		if(eoi == true) {																			//Check for lines after end, report error
			string error = "(Location: " + to_string(loc) + ") Lines after end statement";
			Errors::RecordError(error);
			break;
		}
		translation = m_inst.TranslateInstruction(buff, loc);										//Translate line and store into variable
		if(translation == pair<int, string>(0, "end")) { eoi = true; }								//Trip flag for end of instructions
		else if(translation != pair<int, string>(0, "n/a")) { m_code.push_back(translation); }		//Ignore any n/a instructions and load onto vector
						
		loc = m_inst.LocationNextInstruction(loc);													//Get location of next instruction
	}

	cout << "Press Enter to continue...";
	cin.ignore();
}/*void Assembler::PassII();*/

/*
NAME

	RunProgramInEmulator - Runs the program just parsed in the emulator

SYNOPSIS

	void PassII( );

DESCRIPTION

	This function takes the existing machine code and feeds it to the emulator,

Returns
	
	Returns nothing

Author
	
	Adam Roberts

*/
/**/
void Assembler::RunProgramInEmulator()
{
	if (Errors::checkForErrors()) { return; }														//Check for errors from Pass I&II
	
	for (vector<pair<int, string>>::iterator it = m_code.begin(); it != m_code.end(); ++it) {		// Build code and verify
		bool insertion_check = m_emul.insertMemory(it->first, stoi(it->second));
		if (insertion_check == false) {
			string error = "Failed inserting command " + to_string(it->first) + " " + 
				it->second + " into emulator memory";
			Errors::RecordError(error);
		}
	}
	
														
	if (!m_emul.runProgram()) {																		// Run program and verify it goes
		string error = "Error running the emulator";
		Errors::RecordError(error);
	}

	Errors::checkForErrors();																		//Check for errors from emulator

	cout << "Press Enter to continue...\n";
	cin.ignore();
}/*void Assembler::RunProgramInEmulator();*/
