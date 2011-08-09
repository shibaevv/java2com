////////////////////////////////////////////////////////////////////////////////
// Company:    AQIS                                                           //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------

#ifndef ustringH
#define ustringH

//#include <wtypes.h>
#include <windows.h>
#include <limits.h>
//#include <oleauto.h>

//---------------------------------------------------------------------------
bool ustrncpy( char * p1, const wchar_t * p2, size_t c = INT_MAX );
bool ustrncpy( wchar_t * p1, const wchar_t * p2, size_t c = INT_MAX );
bool ustrncpy( char * p1, const char * p2, size_t c = INT_MAX );
bool ustrncpy( wchar_t * p1, const char * p2, size_t c = INT_MAX );

//bool ustrncpy( unsigned short * pTarget, const char * pSource, size_t c = INT_MAX );

/*
int ustrcmp(const wchar_t * p1, const wchar_t * p2); 
int ustrcmp(const char * p1,    const wchar_t * p2); 
int ustrcmp(const wchar_t * p1, const char * p2); 
int ustrcmp(const char * p1,    const char * p2); 
*/

#endif
