// LegalCharacters.cpp: implementation of the LegalCharacters class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ResourceManager.h"
#include "LegalCharacters.h"

#include "IOUtils.h"

#include <string>

#include <boost/regex.hpp>

#include <cstdlib>
//#include <iostream>

using namespace std;
//using namespace boost;

/*
extern Regex RXwhite;      // = "[ \n\t]+"
extern Regex RXint;        // = "-?[0-9]+"
extern Regex RXdouble;     // = "-?\\(\\([0-9]+\\.[0-9]*\\)\\|
                           //    \\([0-9]+\\)\\|
                           //    \\(\\.[0-9]+\\)\\)
                           //    \\([eE][---+]?[0-9]+\\)?"
extern Regex RXalpha;      // = "[A-Za-z]+"
extern Regex RXlowercase;  // = "[a-z]+"
extern Regex RXuppercase;  // = "[A-Z]+"
extern Regex RXalphanum;   // = "[0-9A-Za-z]+"
extern Regex RXidentifier; // = "[A-Za-z_][A-Za-z0-9_]*"
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LegalCharacters::LegalCharacters()
{
	pXMLProcessor = new XMLProcessor();
}

LegalCharacters::~LegalCharacters()
{
	delete pXMLProcessor;
}

// we can use xml parser for regular expression validation
// or BOOST library
// 3rd party regular expression library to avoid overhead of xml parser
void LegalCharacters::Validate( const char * pData ) throw()
{
	//ValidateXML(pData);
	ValidateRegex(pData);
}

void LegalCharacters::ValidateXML( const char * pData ) throw()
{
	// get schema (with validate pattern)
	ParameterData * param = ResourceManager::GetInstance()->GetParameterData( ParameterData::ILLEGAL_CHARACTERS );
	if ( !param )
		throw Exception( "Failed to get LEGAL_CHARACTERS from configuratin file.\n" );

	const char * pSchema = param->GetValue();


	std::string s;
	s.append( "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" );
	s.append( "<msg>" );
	s.append( "<![CDATA[" );
	s.append( pData );

	// message cannot contain the string "]]>"
	std::string::size_type position;
/*
	if ( ( position = s.find( "]]>" ) ) != std::string::npos ) {
		char buffer[33];
		ltoa( position, buffer, 10 );

		string msg( "Found ]]> at position " );
		msg.append( buffer );
		msg.append( "." );

		throw Exception( msg.c_str() );
	}
*/
    while( ( position = s.find( "]]>" ) ) != std::string::npos) {
		s.replace( position, 3, "XUY");
    }


	s.append( "]]>" );
	s.append( "</msg>" );

	//IOUtils::Write( s.c_str(), "LegalCharacters.txt", "c:\\" );

	pXMLProcessor->Validate( s.c_str(), pSchema );

}

void LegalCharacters::ValidateRegex( const char * pData ) throw()
{
	// get schema (with validate pattern)
	ParameterData * param = ResourceManager::GetInstance()->GetParameterData( ParameterData::ILLEGAL_CHARACTERS );
	if ( !param )
		throw Exception( "Failed to get ILLEGAL_CHARACTERS from configuratin file.\n" );

//IOUtils::Write( param->GetValue(), "ILLEGAL_CHARACTERS.txt", "c:\\" );

	boost::regex expression( param->GetValue() );//, boost::regbase::normal );
	//boost::regex expression( "[^\\d[:alpha:]\\s\\x21-\\x2F\\x3A-\\x3F\\x40\\x5B-\\x5F\\x60\\x7B-\\x7E]" );

	boost::cmatch what;

	if ( boost::regex_search( 
			pData,
			what, 
			expression,
			boost::match_any) )
		throw Exception( "ILLEGAL_CHARACTER(S) found.\n" );

	if ( what[0].matched )
		throw Exception( "ILLEGAL_CHARACTER(S) found (2).\n" );

	// what[0] contains the whole string
    // what[1] contains the response code
    // what[2] contains the separator character
    // what[3] contains the text message.
    //return atoi(what[1].first);

}
