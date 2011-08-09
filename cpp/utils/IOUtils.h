////////////////////////////////////////////////////////////////////////////////
// Company:    AQIS                                                           //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    input/output utilities										  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// IOUtils.h: interface for the IOUtils class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_IOUTILS_H__72C8220A_ED9D_4015_B072_0DC8E58BF581__INCLUDED_)
#define AFX_IOUTILS_H__72C8220A_ED9D_4015_B072_0DC8E58BF581__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IOUtils  
{
private:
	IOUtils();
	~IOUtils();

public:
	static char * Read( 
		const char * pFileName );

	static void Write( 
		const char * pData, 
		const char * pFileName, 
		const char * pDir, 
		long * pLength = 0, 
		bool writeLength = false );
	static void Write( 
		const unsigned char * pData, 
		const char * pFileName, 
		const char * pDir, 
		long * pLength, 
		bool writeLength = false );

};

#endif // !defined(AFX_IOUTILS_H__72C8220A_ED9D_4015_B072_0DC8E58BF581__INCLUDED_)
