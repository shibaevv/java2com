////////////////////////////////////////////////////////////////////////////////
// Company:    AQIS                                                           //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    IValidator implementation (check for legal/printable characters//
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// LegalCharacters.h: interface for the LegalCharacters class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEGALCHARACTERS_H__14A36264_A286_4578_B7AF_0FA7CFB6D86F__INCLUDED_)
#define AFX_LEGALCHARACTERS_H__14A36264_A286_4578_B7AF_0FA7CFB6D86F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Validator.h"

#include "XMLProcessor.h"

class LegalCharacters : public IValidator {
private:

	XMLProcessor * pXMLProcessor;

	void ValidateXML( const char * pData ) throw();
	void ValidateRegex( const char * pData ) throw();

public:
	LegalCharacters();
	virtual ~LegalCharacters();

	// IValidator::Validate() implementation
	void Validate( const char * pData ) throw();

};

#endif // !defined(AFX_LEGALCHARACTERS_H__14A36264_A286_4578_B7AF_0FA7CFB6D86F__INCLUDED_)
