//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H
#pragma once
#include <vector>
#include <sstream>

class Instruction {

public:

    enum InstructionType {													// Enumerator of possible instruction types.
        ST_MachineLanguage, 												// A machine language instruction.
        ST_AssemblerInstr,  												// Assembler Language instruction.
        ST_Comment,          												// Comment or blank line.
        ST_End                   											// End instruction.
    };
    
    InstructionType ParseInstruction(string a_buff);						// Parse the Instruction.
	pair<int, string> TranslateInstruction(string a_buff, int a_loc);		// Translate code into machine language.
    int LocationNextInstruction(int a_loc);									// Compute location of the next instruction.
    inline string &GetLabel( ) { return m_Label; };							// To access the label.
    inline bool isLabel( ) { return ! m_Label.empty(); };					// To determine if a label is blank.


private:

    string m_Label;															// The label.
    string m_OpCode;														// The symbolic op code.
    string m_Operand;														// The operand.
	string m_instruction;													// The original instruction.
	InstructionType m_type;													// The type of instruction.
	vector<string> m_parsed_inst;											// The collection of parsed instructions

	int opCode(string a_buff);												// Returns opCode
	string padString(string a_buff, int a_size);							// Corrects spacing for string variables
};
#endif

