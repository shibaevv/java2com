// IOUtils.cpp: implementation of the IOUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOUtils.h"
#include "Date.h"

#include <iostream>
#include <fstream>
#include <iomanip>

//#include <stdio.h>
//#include <stdlib.h>
//#include <direct.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IOUtils::IOUtils()
{

}

IOUtils::~IOUtils()
{

}

char * IOUtils::Read( const char * pFileName )
{

   char * pData = NULL;

   // read from file (if exists and not empty)
   ifstream is;
   is.open( pFileName, ios::binary );//, ios_base::binary );
   if ( !is.eof() ) {
      
	  size_t length;
	  is >> length;

	  if ( length > 0 ) {
	     pData = new char[ length ];
         is >> pData;
      }

	  is.close();

   }

   // !!! has to be deleted in caller ( delete pData; ) !!!
   return pData;	

}

void IOUtils::Write( 
	const char * pData, 
	const char * pFileName, 
	const char * pDir, 
	long * pLength, 
	bool writeLength )
{
	char path[ _MAX_PATH ];
	sprintf( path, "%s\\%s", pDir, pFileName );

    long length = pLength == 0 ? strlen( pData ) : *pLength;

	// write to file (if does not exists)
	ofstream os;
	os.open( path, ios_base::binary );
	try {
		os.clear();
   
		if ( writeLength )
			os << length << endl;

		for ( long i = 0; i < length; i++ )
			os << pData[i];
      
		os.close();

	} catch (...) {
		os.close();
		throw;
	}

}

void IOUtils::Write( 
	const unsigned char * pData, 
	const char * pFileName, 
	const char * pDir, 
	long * pLength, 
	bool writeLength )
{
	char path[ _MAX_PATH ];
	sprintf( path, "%s\\%s", pDir, pFileName );

    // write to file (if does not exists)
    ofstream os;
    os.open( path, ios_base::binary );
	try {
		os.clear();
   
		if ( writeLength )
			os << *pLength << endl;

		for ( long i = 0; i < *pLength; i++ )
		   os << pData[i];
      
		os.close();

	} catch (...) {
		os.close();
		throw;
	}

}

