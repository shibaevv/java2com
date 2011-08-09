//---------------------------------------------------------------------------

#include "stdafx.h"
#include "ustring.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)

//inline
bool ustrncpy( char * p1, const wchar_t * p2, size_t c ) {
   size_t cb = wcstombs( p1, p2, c );
   return cb != c && cb != (size_t)-1;
}

//inline
bool ustrncpy( wchar_t * p1, const wchar_t * p2, size_t c ) {
    wcsncpy( p1, p2, c );
    return p1[c - 1] == 0;
}

//inline
bool ustrncpy( char * p1, const char * p2, size_t c ) {
    strncpy( p1, p2, c );
    return p1[c - 1] == 0;
}

//inline
bool ustrncpy( wchar_t * p1, const char * p2, size_t c ) {
   size_t cb = mbstowcs( p1, p2, c );
   return cb != c && cb != (size_t)-1;
}

/*
//inline
bool ustrncpy( unsigned short * pTarget, const char * pSource, size_t c ) {
	while(*pSource) {
		*pTarget = *pSource;
		pSource++;
		pTarget++;
	}
	*pTarget = 0;
   return true;

   //strncpy( pTarget, pSource, c );
   //return pTarget[c - 1] == 0;
}
*/

/*
int ustrcmp(const wchar_t * p1, const wchar_t * p2) {
	return wcscmp( p1, p2 );
}
int ustrcmp(const char * p1, const wchar_t * p2) {
	char * _p2 = new char[ wcslen( p2 ) + 1 ];
	if ( ustrncpy( _p2, p2 ) ) {
		int res = strcmp( p1, (const char * ) _p2 );
		delete [] _p2;
		return res;
	}
	delete [] _p2;
	throw "FAILED ustrcmp(const char * p1, const wchar_t * p2)";
}
int ustrcmp(const wchar_t * p1, const char * p2) {
	return ustrcmp( p2, p1 );
}
int ustrcmp(const char * p1, const char * p2) {
	return strcmp( p1, p2 );
}
*/
/*
int _mbscmp(
   const unsigned char *string1,
   const unsigned char *string2 
);
*/

