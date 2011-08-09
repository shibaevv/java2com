////////////////////////////////////////////////////////////////////////////////
// Company:    AQIS                                                           //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    DateTime utilities											  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// Date.h: interface for the Date class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_DATE_H__DB2C70E5_1C29_437E_9EE6_A531FF7FA758__INCLUDED_)
#define AFX_DATE_H__DB2C70E5_1C29_437E_9EE6_A531FF7FA758__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <time.h>

class Date  
{
private:
	char * timeBuf;
public:
	Date();
	~Date();

	char * ToString();

	tm * GetGMTime();
	tm * GetLocalTime();

	static void GetDateTimeStamp( 
		char * pBuffer, 
		const char * pPattern = "ccyymmddhhmmsszzz" );

};

#endif // !defined(AFX_DATE_H__DB2C70E5_1C29_437E_9EE6_A531FF7FA758__INCLUDED_)
