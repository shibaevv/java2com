////////////////////////////////////////////////////////////////////////////////
// Company:    Argus Software                                                 //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    wrapper class												               //
//			   handle memory allocation/deallocation						            //
////////////////////////////////////////////////////////////////////////////////
// ubstr.h: interface for the UBSTR class.
//
//////////////////////////////////////////////////////////////////////


#ifndef ubstrH
#define ubstrH

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wtypes.h>
#include <limits.h>
#include <oleauto.h>

class UBSTR  
{
private:
	BSTR m_bstr;

	inline bool equals(const UBSTR & rhs) const { return wcscmp( m_bstr, rhs.m_bstr ) == 0; }
	inline bool less(const UBSTR & rhs) const { return wcscmp( m_bstr, rhs.m_bstr ) < 0; }

public:
	UBSTR( const char * psz )
	  : m_bstr( ::SysAllocStringLen( 0, strlen( psz ) ) )
	{
		mbstowcs( m_bstr, psz, INT_MAX );
	}

	UBSTR( const wchar_t * pwsz )
	  : m_bstr( ::SysAllocString( pwsz ) ) {}

	~UBSTR() { ::SysFreeString( m_bstr ); }

	operator BSTR () const { return m_bstr; }
	//operator BSTR* () { return &m_bstr; }

	BSTR* operator&() { return &m_bstr; }
	//BSTR* operator*() { return &m_bstr; }

	friend bool operator == (const UBSTR & lhs, const UBSTR & rhs) { return lhs.equals(rhs); }
	friend bool operator != (const UBSTR & lhs, const UBSTR & rhs) { return ! (lhs == rhs); }
	friend bool operator <  (const UBSTR & lhs, const UBSTR & rhs) { return lhs.less(rhs); }
	friend bool operator >  (const UBSTR & lhs, const UBSTR & rhs) { return rhs < lhs; }
	friend bool operator <= (const UBSTR & lhs, const UBSTR & rhs) { return ! (lhs > rhs); }
	friend bool operator >= (const UBSTR & lhs, const UBSTR & rhs) { return rhs <= lhs; }

};


#endif // !defined(ubstrH)
