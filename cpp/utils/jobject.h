////////////////////////////////////////////////////////////////////////////////
// Company:    Argus Software                                                 //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    wrapper class												               //
//			   handle jobject creation             						            //
////////////////////////////////////////////////////////////////////////////////
// ubstr.h: interface for the UBSTR class.
//
//////////////////////////////////////////////////////////////////////

#ifndef jobjectH
#define jobjectH

#include <jni.h>

//---------------------------------------------------------------------------
namespace argus {

class jobject
{
private:
	::jobject m_jobject;

public:
	jobject( const char * psz )
	  : m_jobject( ::SysAllocStringLen( 0, strlen( psz ) ) )
	{
		mbstowcs( m_bstr, psz, INT_MAX );
	}

	jobject( const wchar_t * pwsz )
	  : m_jobject( ::SysAllocString( pwsz ) ) {}

	~jobject() { ::SysFreeString( m_bstr ); }

	operator jobject () const { return m_jobject; }
	//operator jobject* () { return &m_jobject; }

	jobject* operator&() { return &m_jobject; }
	//jobject* operator*() { return &m_jobject; }

};

}

#endif
