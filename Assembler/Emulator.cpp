#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"
#include "FileAccess.h"
#include <iomanip>
#include <iostream>

/*
NAME

	insertMemory - machine code into memory.

SYNOPSIS

	bool insertMemory(int a_location, int a_contents)

DESCRIPTION

	This function will verify the program is still with in memory bounds, and if so 
	it will insert the translated code into the specific location of memory.

Returns
	
	Returns true if successful, false if location is out of bounds

Author
	
	Adam Roberts

*/
/**/
bool emulator::insertMemory(int a_location, int a_contents)
{
	if (a_location < MEMSZ && a_location >= 0) { m_memory[a_location] = a_contents; }
	else {
		string error = "Memory overflow";
		Errors::RecordError(error);
		return false;
	}
	return true;
}/*bool emulator::insertMemory( int a_location, int a_contents );*/

/*
NAME

	runProgram - executes the machine code stored in memory.

SYNOPSIS

	runProgram()

DESCRIPTION

	This function cycles through the stored memory and executes the stored code.

Returns
	
	Returns true if successfully finishes, false if not.

Author
	
	Adam Roberts

*/
/**/
bool emulator::runProgram()
{
	m_loc = 100;
	 
	do{
		m_opcode = m_memory[m_loc] / 100000;
		m_operand = m_memory[m_loc] % 100000;
		
		switch (m_opcode) {
		case 0:			
			m_loc++;
			break;
		case 1:
			add();
			break;
		case 2:
			sub();
			break;
		case 3:
			mult();
			break;
		case 4:
			div();
			break;
		case 5:
			load();
			break;
		case 6:
			store();
			break;
		case 7:
			read();
			break;
		case 8:
			write();
			break;
		case 9:
			b();
			break;
		case 10:
			bm();
			break;
		case 11:
			bz();
			break;
		case 12:
			bp();
			break;
		case 13:
			return true;
		}		
	} while (m_loc != MEMSZ);

	return false;
}/*bool emulator::runProgram();*/

/*
NAME

	add - performs the addition function of the language.

SYNOPSIS

	add()

DESCRIPTION

	This function adds the existing accumulator and the number stored at the given location.

Returns
	
	Returns nothing.

Author
	Adam Roberts

*/
/**/
void emulator::add()
{
	int sum = accumulator + m_memory[m_operand];

	if (sum > 999'999 || sum < -999'999) {
		cout << "Accumulator overflow\n";
		return;
	}

	accumulator = sum;
	m_loc++;
}/* void emulator::add(); */

/*
NAME

	sub - performs the subtraction function of the language.

SYNOPSIS

	sub()

DESCRIPTION

	This function subtracts the existing accumulator and the number stored at the given location.

Returns
	
	Returns nothing.

Author
	
	Adam Roberts

*/
/**/
void emulator::sub()
{
	int difference = accumulator - m_memory[m_operand];

	if (difference > 999'999 || difference < -999'999) {
		cout << "Accumulator overflow\n";
		return;
	}

	accumulator = difference;
	m_loc++;
} /* void emulator::sub() */

/*
NAME

	mult - performs the multiplication function of the language.

SYNOPSIS

	mult()

DESCRIPTION

	This function multiplies the existing accumulator and the number stored at the given location.

Returns

	Returns nothing.

Author

	Adam Roberts

*/
/**/
void emulator::mult()
{
	int product = accumulator * m_memory[m_operand];

	if (product > 999'999 || product < -999'999) {
		cout << "Accumulator overflow\n";
		return;
	}

	accumulator = product;
	m_loc++;
} /* void emulator::mult() */

/*
NAME

	div - performs the division function of the language.

SYNOPSIS

	div()

DESCRIPTION

	This function divides the existing accumulator and the number stored at the given location.

Returns
	
	Returns nothing.

Author
	
	Adam Roberts

*/
/**/
void emulator::div()
{
	int dividend = accumulator / m_memory[m_operand];

	if (dividend > 999'999 || dividend < -999'999) {
		cout << "Accumulator overflow\n";
		return;
	}

	accumulator = dividend;
	m_loc++;
} /* void emulator::div() */

/*
NAME

	load - performs the loading function of the language.

SYNOPSIS

	load()

DESCRIPTION

	This function loads the number stored at the given location into the accumulator.

Returns

	Returns nothing.

Author

	Adam Roberts

*/
/**/
void emulator::load()
{
	accumulator = m_memory[m_operand];
	m_loc++;
} /* void emulator::load() */

/*
NAME

	store - performs the store function of the language.

SYNOPSIS

	add()

DESCRIPTION

	This function stores the existing accumulator into the given location.

Returns
	
	Returns nothing.

Author

	Adam Roberts

*/
/**/
void emulator::store()
{
	m_memory[m_operand] = accumulator;
	m_loc++;
} /* void emulator::store() */

/*
NAME

	read - performs the read function of the language.

SYNOPSIS

	read()

DESCRIPTION

	This function reads user input and stores it at the given location.

Returns

	Returns nothing.

Author

	Adam Roberts

*/
/**/
void emulator::read()
{
	int input;

	do {
		cout << "Please input a number: ";
		cin >> input;
		while(!cin) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Don't be dick! Input a number: ";
			cin >> input;
		}
	} while (input > 999'999|| input < -999'999);

	m_memory[m_operand] = input;
	m_loc++;
	
} /* void emulator::read() */

/*
NAME

	write - performs the write function of the language.

SYNOPSIS

	write()

DESCRIPTION

	This function writes the number stored at the given location out to the screen.

Returns
	
	Returns nothing.

Author
	
	Adam Roberts

*/
/**/
void emulator::write()
{
	cout << m_memory[m_operand] << endl;
	m_loc++;
} /* void emulator::write() */

/*
NAME

	b - performs a relocation function of the language.

SYNOPSIS

	b()

DESCRIPTION

	This function moves the location to the number stored in the current location.

Returns
	
	Returns nothing.

Author
	
	Adam Roberts

*/
/**/
void emulator::b()
{
	m_loc = m_operand;
} /* void emulator::b() */

/*
NAME

	bm - performs a relocation function of the language.

SYNOPSIS

	bm()

DESCRIPTION

	This function moves the location to the number stored in the current location 
	iff the accumulator is less than 0.

Returns
	
	Returns nothing.

Author
	
	Adam Roberts

*/
/**/
void emulator::bm()
{
	if(accumulator < 0){ m_loc = m_operand; }
	else{ m_loc++; }
} /* void emulator::bm() */

/*
NAME

	bz - performs a relocation function of the language.

SYNOPSIS

	bz()

DESCRIPTION

	This function moves the location to the number stored in the current location
	iff the accumulator is equal to 0.

Returns
	
	Returns nothing.

Author
	
	Adam Roberts

*/
/**/
void emulator::bz()
{
	if(accumulator == 0){ m_loc = m_operand; }
	else{ m_loc++; }
} /* void emulator::bz() */

/*
NAME

	bp - performs a relocation function of the language.

SYNOPSIS

	bp()

DESCRIPTION

	This function moves the location to the number stored in the current location
	iff the accumulator is more than 0.

Returns

	Returns nothing.

Author

	Adam Roberts

*/
/**/
void emulator::bp()
{
	if(accumulator > 0){ m_loc = m_operand; }
	else{ m_loc++; }
} /* void emulator::bp() */


