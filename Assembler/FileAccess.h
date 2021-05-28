//
//		File access to source file.
//
#ifndef _FILEACCESS_H
#define _FILEACCESS_H

#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

public:
    
    FileAccess( int argc, char *argv[] );				// Opens the file.
    ~FileAccess( );										// Closes the file.
    bool GetNextLine( string &a_buff );					// Get the next line from the source file.
    void rewind( );										// Put the file pointer back to the beginning of the file.

private:

    ifstream m_sfile;									// Source file object.
};
#endif

