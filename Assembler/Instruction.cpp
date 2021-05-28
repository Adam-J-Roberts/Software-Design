#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"
#include "SymTab.h"
#include <iomanip>
#include <iostream>

/*
NAME

	ParseInstruction - Loads each line of code into a vector

SYNOPSIS

	ParseInstruction(string a_buff);

DESCRIPTION

	This function will first remove comments, it then loads it into a vector, 
	and then identifies it's Instruction type.

Returns

	Returns InstructionType

Author

	Adam Roberts

*/
/**/
Instruction::InstructionType Instruction::ParseInstruction(string a_buff)
{
	m_Label.clear();
	m_OpCode.clear();
	m_Operand.clear();
	m_instruction = a_buff;
	m_parsed_inst.clear();
	m_parsed_inst.resize(0);
	string temp;
	
	//Delete comments
	int comStat = m_instruction.find(';');
	if (comStat != -1){ m_instruction = m_instruction.substr(0, comStat); }
	//Loading passed instructions into vector
	stringstream ss(m_instruction);
	while (ss >> temp){ m_parsed_inst.push_back(temp); }
	//Sorting based on Instruction type
	if (m_parsed_inst.empty()){ m_type = InstructionType(2); }
	else if (m_parsed_inst[0] == "org") { m_type = InstructionType(1); }
	else if (m_parsed_inst[0] == "halt") { m_type = InstructionType(0); }
	else if (m_parsed_inst[0] == "end") { m_type = InstructionType(3); }
	else if (m_parsed_inst.size() == 2) { m_type = InstructionType(0); }
	else {
		m_Label = m_parsed_inst[0];
		if (m_parsed_inst[1] == "dc" || m_parsed_inst[1] == "ds"){ m_type = InstructionType(1); }
		else{ m_type = InstructionType(0); }
	}

	return m_type;
}/* Instruction::InstructionType Instruction::ParseInstruction(string a_buff) */

/*
NAME

	TranslateInstruction - Loads each line of code into a vector

SYNOPSIS

	TranslateInstruction(string a_buff, int a_loc);

DESCRIPTION

	This function will take in a line of duck code and a loc, and translate those into machine code.  
	It then will display the translations

Returns

	Returns pair<int, string>

Author

	Adam Roberts

*/
/**/
pair<int, string> Instruction::TranslateInstruction(string a_buff, int a_loc)
{

	Instruction::InstructionType st = ParseInstruction(a_buff);

	//Check word count/vector elements
	if(m_parsed_inst.size() > 3) {
		string error = "(Location: " + to_string(a_loc) + ") Too many words.";
		Errors::RecordError(error);
	}

	//Translate instructions into machine code
	if(st == InstructionType(0)) {
		string assemblyCode; 
		int loc = 0;
		switch(m_parsed_inst.size()) {
			//Identify words in instruction, assign code accordingly
			case (1):																				
				m_OpCode = m_parsed_inst[0];
				if(opCode(m_OpCode) != -1) {
					//Only halt commands should be one word long.  Assign machine code accordingly
					if(m_OpCode == "halt") { assemblyCode = "1300000"; }							
					else {																			
						string error = "(Location: " + to_string(a_loc) + ") Unknown m_Operand";
						Errors::RecordError(error);
						assemblyCode = to_string(opCode(m_OpCode)) + "?????";
						assemblyCode = padString(assemblyCode, 7);
					}
				}
				else {
					string error = "(Location: " + to_string(a_loc) + ") Unknown command";
					Errors::RecordError(error);
					assemblyCode = "???????";
				}
				break;
			case(2):
				// Two words contains neither halt nor label.  Assign machine code accordingly
				m_OpCode = m_parsed_inst[0];
				m_Operand = m_parsed_inst[1];
				if(opCode(m_OpCode) != -1) {
					assemblyCode = padString(to_string(opCode(m_OpCode)), 2);
					if (SymbolTable::LookupSymbol(m_Operand, loc)) { assemblyCode += padString(to_string(loc), 5); }
					else {
						string error = "(Location: " + to_string(a_loc) + ") Unknon m_Operand";
						Errors::RecordError(error);
						assemblyCode += "?????";
					}
				}
				else {
					string error = "(Location: " + to_string(a_loc) + ") Unknown command";
					Errors::RecordError(error);
					assemblyCode = "???????";
				}
				break;
			case(3):
				//If 3 words long, code contains a label.  Assign machine code accordingly
				m_Label = m_parsed_inst[0];
				m_OpCode = m_parsed_inst[1];
				m_Operand = m_parsed_inst[2];

				if(opCode(m_OpCode) != -1) {
					assemblyCode = padString( (to_string(opCode(m_OpCode))) , 2);
					if(SymbolTable::LookupSymbol(m_Operand, loc)) { assemblyCode += padString(to_string(loc), 5); }
					else {
						string error = "(Location: " + to_string(a_loc) + ") Unknon m_Operand";
						Errors::RecordError(error);
						assemblyCode += "?????";
					}
				}
				else {
					string error = "(Location: " + to_string(a_loc) + ") Unknown command";
					Errors::RecordError(error);
					assemblyCode = "???????";
				}
				break;
			default:
				// Improperly formatted code. Assign machine code accordingly
				assemblyCode = "???????";
				break;
		}
	//Display translated instructions
		cout << setw(12) << left << a_loc << setw(12) << left << assemblyCode << a_buff <<endl;
		return pair<int, string>(a_loc, assemblyCode);
	}

	if(st == InstructionType(1) && m_parsed_inst.size() >= 3 && m_parsed_inst[1] == "dc") {
		cout << setw(12) << left << a_loc << setw(12) << left << padString(m_parsed_inst[2], 7) << a_buff << endl;
	}
	else if(st == InstructionType(1)) { cout << setw(12) << left << a_loc << setw(12) << left << "" << a_buff << endl; }
	else { cout << setw(24) << " " << a_buff << endl; }

	if(st == InstructionType(3)) { return pair<int, string>(0, "end"); }
		
	return pair<int, string>(0, "n/a");
}/* pair<int, string> Instruction::TranslateInstruction(string a_buff, int a_loc) */

/*
NAME

	LocationNextInstruction - Loads each line of code into a vector

SYNOPSIS

	LocationNextInstruction(int a_loc);

DESCRIPTION

	This function will take in a location of current instructions, and 
	parse it out to find the next instruction location.

Returns

	Returns int

Author

	Adam Roberts

*/
/**/
int Instruction::LocationNextInstruction(int a_loc)
{
	string first, second, third;
	stringstream ss(m_instruction);

	switch (m_type) {
	case ST_AssemblerInstr:
		ss >> first >> second >> third;
		if (first == "org") { return stoi(second); }
		else if (second == "ds") { return a_loc + stoi(third); }
	case ST_MachineLanguage:
		return a_loc + 1;
	default:  
		return a_loc;
	}
} /* int Instruction::LocationNextInstruction(int a_loc) */

/*
NAME

	opCode - Parses computer code to assign an opCode

SYNOPSIS

	opCode(string a_buff);

DESCRIPTION

	This function will take in a line of duck code and returns the corresponding opCode

Returns

	Returns int

Author

	Adam Roberts

*/
/**/
int Instruction::opCode(string a_buff)
{
	map<string, int> opCodeMap{
		{ "add", 1 }, { "sub", 2 }, { "mult", 3 }, { "div", 4 }, { "load", 5 }, { "store", 6 }, { "read", 7 }, 
		{ "write", 8 }, { "b", 9 }, { "bm", 10 }, { "bz", 11 }, { "bp", 12 }, { "halt", 13 }
	};

	if(opCodeMap[a_buff] > 0 && opCodeMap[a_buff] < 14){ return opCodeMap[a_buff]; }
	
	return -1;
}/* int Instruction::opCode(string a_buff) */

/*
NAME

	padString - pads a string with 0's to fit the given machine language format

SYNOPSIS

	padString(string a_buff, int a_size);

DESCRIPTION

	This function will take in a string and an int size and ad 0's accordingly to make the string fit.

Returns

	Returns string

Author

	Adam Roberts

*/
/**/
string Instruction::padString(string a_buff, int a_size)
{
	if(static_cast<int>(a_buff.size()) >= a_size) { return a_buff; }
	for(int i = a_buff.size(); i < a_size; i++){
		a_buff.insert(0, "0"); 
	}
		
	return a_buff;
}/*  string Instruction::padString(string a_buff, int a_size)*/