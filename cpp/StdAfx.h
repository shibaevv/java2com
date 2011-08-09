// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E030AF07_4AC5_4DE5_9D4F_2BDC897D7F2D__INCLUDED_)
#define AFX_STDAFX_H__E030AF07_4AC5_4DE5_9D4F_2BDC897D7F2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// disable warning C4786: symbol greater than 255 character,
// okay to ignore
#pragma warning(disable: 4786)

// Insert your headers here
//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define _WIN32_WINNT 0x403

#include <windows.h>
//#include <olectl.h>

// TODO: reference additional headers your program requires here
#include <jni.h>
#include <iostream>

#include "utils\ubstr.h"
#include "utils\ustring.h"
#include "utils\jni_utils.h"
#include "utils\LicenseChecker.h"
#include "include\Java2COMLicenseChecker.h"
#include "include\dispatch.h"
#include "include\dispatchMap.h"
#include "include\dispatchUtils.h"
#include "include\variant.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E030AF07_4AC5_4DE5_9D4F_2BDC897D7F2D__INCLUDED_)
