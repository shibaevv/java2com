// Exception.h: interface for the Exception class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCEPTION_H__3B67A7EA_0D3C_4628_B737_15DA1DDA6146__INCLUDED_)
#define AFX_EXCEPTION_H__3B67A7EA_0D3C_4628_B737_15DA1DDA6146__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Exception  
{
private:
   char * pMsg;
public:
	Exception( const char * pMsg )
		: pMsg( new char[ strlen( pMsg ) + 1 ] )
	{
		strncpy( this->pMsg, pMsg, strlen( pMsg ) );
		this->pMsg[ strlen( pMsg ) ] = 0x00;
	}
	virtual ~Exception() 
	{ 
		delete [] pMsg; 
	}

	virtual const char * GetMessage() const { return pMsg; }
};

#endif // !defined(AFX_EXCEPTION_H__3B67A7EA_0D3C_4628_B737_15DA1DDA6146__INCLUDED_)
