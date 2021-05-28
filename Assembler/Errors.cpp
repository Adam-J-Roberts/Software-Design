#include "stdafx.h"
#include "Errors.h"
#include <iomanip>

std::vector<string> Errors::m_ErrorMsgs;

/*
NAME

	checkForErrors - checks for any errors reported.

SYNOPSIS

	checkForErrors()

DESCRIPTION

	This function verifies the errors vector is empty. If not it displays any errors found

Returns

	Returns true if error vector is empty, returns false otherwise.

Author

	Adam Roberts

*/
/**/
bool Errors::checkForErrors() {
	if (!Errors::Empty()) {
		cout << "Errors were encountered during compilation...\nExiting emulation\n";
		Errors::DisplayErrors();
		return true;
	}
	else { return false; }
}/* bool Errors::checkForErrors(); */

/*
NAME

	DisplayErrors - displays any errors reported.

SYNOPSIS

	DisplayErrors()

DESCRIPTION

	This function displays any errors previously reported.

Returns

	Returns nothing.

Author

	Adam Roberts

*/
/**/
void Errors::DisplayErrors()
{
     int count = 0;
     for (vector<string>::iterator is = m_ErrorMsgs.begin(); is != m_ErrorMsgs.end(); ++is) {
          cout << "ERROR " << setw(2) << count++ << ": " << *is << endl;
     }
}/* void Errors::DisplayErrors() */
