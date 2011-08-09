//---------------------------------------------------------------------------
/*
Type Description Interfaces

Type description interfaces provide a way to read and bind to the descriptions
of objects in a type library. These descriptions are used by ActiveX clients
when they browse, create, and manipulate ActiveX (Automation) objects.

The type description interfaces described in this chapter include:

    * ITypeLib — Retrieves information about a type library.
    * ITypeLib2 — Contains additional type library retrieval actions.
    * ITypeInfo — Reads the type information within the type library.
    * ITypeInfo2 — Contains additional type information retrieval actions.
    * ITypeComp — Contains type lookup and binding methods.

This chapter also describes functions for loading, registering, and querying type libraries.
*/

#include "stdafx.h"
#include "TypeLib.h"

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

#include <iostream>
#include <iomanip>

bool readData(JNIEnv * env, ::ITypeInfo* pTypeInfo, jobject obj, jobject collection);

using namespace argus;

//---------------------------------------------------------------------------
/*
HRESULT LoadTypeLib(szFileName, lplptlib)
OLECHAR FAR* szFileName
ITypeLib FAR* FAR* lplptlib

Loads and registers a type library.
Parameters
   szFileName  Contains the name of the file from which LoadTypeLib should attempt to load a type library.
   lplptlib    On return, contains a pointer to a pointer to the loaded type library.
*/
/*
 * Class:     com_argus_activex_TypeLib
 * Method:    LoadTypeLib
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_TypeLib_LoadTypeLib
  (JNIEnv * env, jobject obj, jstring fileName)
{
	try {
      // jstring to char
      const char * utfChars = env->GetStringUTFChars( fileName, NULL );

      // char to wchar_t
      wchar_t lpsz[512];
      bool res = ustrncpy( lpsz, utfChars, 512 );
      env->ReleaseStringUTFChars( fileName, utfChars );
      if ( !res ) {
         ThrowComException( env, E_FAIL, "LoadTypeLib(...) ustrncpy(...) FAILED!" );
         return 0;
      }

	   ::ITypeLib * pTypeLib = NULL;
	   //::ITypeLib2 * pTypeLib2 = NULL;
   	HRESULT hr = LoadTypeLib(lpsz, &pTypeLib);
	   if ( FAILED(hr) )
   	{
	   	ThrowComException(env, hr, "LoadTypeLib failed.");
		   return 0;
   	}

      
      //Index of the type description whose documentation is to be returned.
      //If index is -1, then the documentation for the library itself is returned.
      BSTR name;
      BSTR docString;
      DWORD helpContext;
      BSTR helpFile;
   	hr = pTypeLib->GetDocumentation(-1, &name, &docString, &helpContext, &helpFile);
	   if ( FAILED(hr) ) {
		   ThrowComException(env, hr, "ITypeLib::GetDocumentation failed.");
		   return 0;
   	}
      setFieldValue(env, obj, "name", NewString(env, name));
      setFieldValue(env, obj, "docString", NewString(env, docString));
      setFieldValue(env, obj, "helpContext", (jint) helpContext);
      setFieldValue(env, obj, "helpFile", NewString(env, helpFile));
      //::SysFreeString(name);
      //::SysFreeString(docString);
      //::SysFreeString(helpFile);

      /////////////////////////////////////////////////////////////////////////////
      // TLIBATTR property
      /////////////////////////////////////////////////////////////////////////////
      ::TLIBATTR * pTLibAttr = NULL;
      hr = pTypeLib->GetLibAttr(&pTLibAttr);
  	   if ( FAILED(hr) ) {
	      ThrowComException(env, hr, "ITypeLib::GetLibAttr failed.");
	      return 0;
  	   }

      argus::jobject_auto tlibAttr( env, "Lcom/argus/activex/TLIBATTR;" );
      //hr = argus::TLIBATTR(env, pTypeLib, pTLibAttr).init(tlibAttr);
      hr = TLIBATTR(env, pTypeLib, pTLibAttr).init(tlibAttr);
      if ( FAILED(hr) ) {
         return 0;
      }
      setObjectFieldValue(env, obj, "tlibAttr", "Lcom/argus/activex/TLIBATTR;", tlibAttr);

      return (jint) pTypeLib;

  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to TypeLib::LoadTypeLib(..)." );
      return 0;
  	}

}

/*
 * Class:     com_argus_activex_TypeLib
 * Method:    readData
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_argus_activex_TypeLib_readData
  (JNIEnv * env, jobject obj, jint pTypeLib)

{

	try {
      if ( !pTypeLib ) {
         ThrowComException( env, DISP_E_EXCEPTION, "Could not cast pTypeLib = 0" );
         return;
      }

      argus::ITypeLib(env, (::ITypeLib *) pTypeLib).init( obj );

  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to ITypeLib::readData(..)." );
  	}

}

