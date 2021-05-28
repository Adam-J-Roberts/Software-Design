#include "stdafx.h"
#include "FileAccess.h"

/*
NAME

	FileAccess - Opens the source code file


SYNOPSIS

	FileAccess( int argc, char *argv[] )

DESCRIPTION

	This function creates a class of FileAccess that is responsible for opening the source
	code, and accessing various parts.

Returns
	
	Creates an instance of the class.

Author
	
	Victor Miller

*/
/**/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 ); 
    }
}/* FileAccess( int argc, char *argv[] ); */

/*
NAME

	~FileAccess - Deconstructs the existing object.


SYNOPSIS

	~FileAccess( )

DESCRIPTION

	This function closes the source code document and destroys the object for reading it.

Returns
	
	Returns nothing

Author
	
	Victor Miller

*/
/**/
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}/* ~FileAccess( ) */

/*
NAME

	GetNextLine - Copies next line of file.


SYNOPSIS

	GetNextLine( string &a_buff )

DESCRIPTION

	This function copies the next line of the file into the passed variable.

Returns
	
	Returns true if successful, false if at end of file.

Author
	
	Victor Miller

*/
/**/
bool FileAccess::GetNextLine( string &a_buff )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_buff );
    
    // Return indicating success.
    return true;
}/* bool FileAccess::GetNextLine( string &a_buff ) */

/*
NAME

	rewind - resets the file location pointer.


SYNOPSIS

	rewind()

DESCRIPTION

	This function moves the file pointer back to the begining

Returns

	Returns nothing.

Author

	Victor Miller

*/
/**/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}/* void FileAccess::rewind( ) */
    
