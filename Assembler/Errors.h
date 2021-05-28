//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
// What other choices do we have to accomplish the same thing?
//
#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>

class Errors {

public:

	static bool checkForErrors();														// Checks for any errors previously reported
    static void InitErrorReporting( ) { m_ErrorMsgs.clear(); };							// Initializes error reports.
    static void RecordError( string &a_emsg ) { m_ErrorMsgs.push_back(a_emsg); };		// Records an error message.
	static void DisplayErrors( );														// Displays the collected error message.
	static bool Empty() { return (m_ErrorMsgs.size() == 0) ? true : false; };			// Displays if any errors have been recorded.

private:

    static vector<string> m_ErrorMsgs;													// Vector holding any existing errors.

	

};
#endif