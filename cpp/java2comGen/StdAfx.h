// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CD8D52C5_0ED3_4B07_8A37_742EF58D5ED3__INCLUDED_)
#define AFX_STDAFX_H__CD8D52C5_0ED3_4B07_8A37_742EF58D5ED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// disable warning C4786: symbol greater than 255 character,
// okay to ignore
#pragma warning(disable: 4786)

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

// TODO: reference additional headers your program requires here
#include <jni.h>
#include <iostream>

#include "..\utils\ubstr.h"
#include "..\utils\ustring.h"
#include "..\utils\jni_utils.h"
#include "..\utils\jobjectArray_auto.cpp"
#include "..\utils\jobject_auto.cpp"
#include "..\include\variant.h"
#include "include\TypeLib.cpp"
#include "include\TypeInfo.cpp"
#include "include\TYPEDESC.cpp"
#include "include\ELEMDESC.cpp"
#include "include\FUNCDESC.cpp"
#include "include\IDLDESC.cpp"
#include "include\SAFEARRAYBOUND.cpp"
#include "include\TypeAttr.cpp"
#include "include\ARRAYDESC.cpp"
#include "include\PARAMDESC.cpp"
#include "include\PARAMDESCEX.cpp"
#include "include\variant.cpp"
#include "include\VARDESC.cpp"
#include "include\ITypeLib.cpp"
#include "include\TLIBATTR.cpp"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CD8D52C5_0ED3_4B07_8A37_742EF58D5ED3__INCLUDED_)
