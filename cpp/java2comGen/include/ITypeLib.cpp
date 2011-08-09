//---------------------------------------------------------------------------
#include "ITypeLib.h"

#include "TLIBATTR.h"
#include "TypeInfo.h"
#include "TypeAttr.h"

#include "jobject_auto.h"
#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>
#include <map>

using namespace argus;


//---------------------------------------------------------------------------
typedef std::map<long, ::ITypeLib*> ITypeLibMap;
typedef std::map<long, ::ITypeLib*>::iterator ITypeLibMapIterator;
ITypeLibMap * pMap = new ITypeLibMap();

void add(::ITypeLib * pTypeLib) {
   long id = (long) pTypeLib;

   ITypeLibMapIterator p = pMap->find( id );
   if ( p == pMap->end() ) {
      pMap->insert( std::make_pair( id, pTypeLib ) );
//std::cout << std::endl << "TypeInfo for the UDT TYPEDESC::GetContainingTypeLib(...) " << pTypeLib << std::endl;
   }

}
void release(long pTypeLib) {
   pMap->erase( pTypeLib );
}
void clear() {
   pMap->clear();
}

//---------------------------------------------------------------------------
argus::ITypeLib * argus::ITypeLib::pTL = NULL;
argus::ITypeLib * argus::ITypeLib::getInstance() {
   return pTL;
}

argus::ITypeLib::ITypeLib(JNIEnv * env, ::ITypeLib * pTypeLib) {
   this->env = env;
   this->pTypeLib = pTypeLib;

   pTL = this;
}

argus::ITypeLib::~ITypeLib() {
   pTL = NULL;

   // release resources
	//pTypeLib->Release();
}

/**
 * get ContainingTypeLib and store its pointer in map/list
 */
HRESULT argus::ITypeLib::addContainingTypeLib(::ITypeInfo * pTypeInfo, ::ITypeLib ** ppTypeLib)
{
   *ppTypeLib = NULL;
   UINT index = 0;
   HRESULT hr = pTypeInfo->GetContainingTypeLib(ppTypeLib, &index);
   if (!FAILED(hr)) {
      add( *ppTypeLib );
   } else {
      std::cerr << "\tFailed TypeInfo for the UDT TYPEDESC::GetContainingTypeLib(...) " << *ppTypeLib << ", hr=" << hr << std::endl;
   }

   return hr;
}

//---------------------------------------------------------------------------
HRESULT argus::ITypeLib::init(jobject obj)
{
   HRESULT hr = E_FAIL;

   BSTR name = NULL;
   BSTR docString = NULL;
   DWORD helpContext = 0;
   BSTR helpFile = NULL;
   ::TLIBATTR * pTLibAttr = NULL;

	try {
      if ( !pTypeLib ) {
         ThrowComException( env, DISP_E_EXCEPTION, "pTypeLib == NULL" );
         return hr;
      }

      clear();
//*
      //Index of the type description whose documentation is to be returned.
      //If index is -1, then the documentation for the library itself is returned.
   	hr = pTypeLib->GetDocumentation(-1, &name, &docString, &helpContext, &helpFile);
	   if ( FAILED(hr) ) {
		   ThrowComException(env, hr, "ITypeLib::GetDocumentation failed.");
		   return hr;
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
      hr = pTypeLib->GetLibAttr(&pTLibAttr);
  	   if ( FAILED(hr) ) {
	      ThrowComException(env, hr, "ITypeLib::GetLibAttr failed.");
	      return hr;
  	   }

      argus::jobject_auto tlibAttr( env, "Lcom/argus/activex/TLIBATTR;" );
      hr = argus::TLIBATTR(env, pTypeLib, pTLibAttr).init(tlibAttr);
      if ( FAILED(hr) ) {
         return 0;
      }
      setObjectFieldValue(env, obj, "tlibAttr", "Lcom/argus/activex/TLIBATTR;", tlibAttr);

//*/
      unsigned int count = pTypeLib->GetTypeInfoCount();
     	//#ifdef DEBUG
      _tprintf(_T("TypeInfoCount=%d\n"), count);
      //#endif
      jobjectArray_auto typeInfoArray( env, count, "Lcom/argus/activex/TypeInfo;");
      setObjectFieldValue(env, obj, "typeInfoArray", "[Lcom/argus/activex/TypeInfo;", typeInfoArray);
      for ( unsigned int i = 0; i < count; i++ )  {
         std::cout << ".";

         ::ITypeInfo * pTypeInfo = NULL;
	      hr = pTypeLib->GetTypeInfo(i, &pTypeInfo);
   	   if ( FAILED(hr) ) {
		      ThrowComException(env, hr, "GetTypeInfo failed.");
		      return hr;
   	   }

         // create new jobject
         jobject_auto jTypeInfo( env, "Lcom/argus/activex/TypeInfo;" );
         env->SetObjectArrayElement(typeInfoArray, i, jTypeInfo);

         hr = TypeInfo(env, pTypeInfo).init(jTypeInfo);
      	if ( FAILED(hr) ) {
            return hr;
         }

      }

      // save other ContainingTypeLib
      // create and set typeLib (int array member)
      long i = 0;
      jobjectArray_auto jtypeLibArray( env, pMap->size(), "Lcom/argus/activex/TypeLib;");
      setObjectFieldValue(env, obj, "typeLibs", "[Lcom/argus/activex/TypeLib;", jtypeLibArray);
      for ( ITypeLibMapIterator p = pMap->begin(); p != pMap->end(); p++ ) {
         //long buf = p->first;
         ::ITypeLib * pContainingTypeLib = p->second;
         if (pTypeLib == pContainingTypeLib) continue;

         // create new jobject
         jobject jtypeLib = jtypeLibArray.NewObject();

         setFieldValue(env, jtypeLib, "pTypeLib", (jint) pContainingTypeLib);

         hr = pContainingTypeLib->GetDocumentation(-1, &name, &docString, &helpContext, &helpFile);
	      if ( FAILED(hr) ) {
		      ThrowComException(env, hr, "ITypeLib::GetDocumentation failed.");
      	   return hr;
         }
         setFieldValue(env, jtypeLib, "name", NewString(env, name));
         setFieldValue(env, jtypeLib, "docString", NewString(env, docString));
         setFieldValue(env, jtypeLib, "helpContext", (jint) helpContext);
         setFieldValue(env, jtypeLib, "helpFile", NewString(env, helpFile));

         /////////////////////////////////////////////////////////////////////////////
         // TLIBATTR property
         /////////////////////////////////////////////////////////////////////////////
         hr = pContainingTypeLib->GetLibAttr(&pTLibAttr);
         if ( FAILED(hr) ) {
	         ThrowComException(env, hr, "ITypeLib::GetLibAttr failed.");
   	      return hr;
         }

         // create new jobject
         jobject_auto tlibAttr( env, "Lcom/argus/activex/TLIBATTR;" );
         hr = TLIBATTR(env, pContainingTypeLib, pTLibAttr).init(tlibAttr);
         if ( FAILED(hr) ) {
            return hr;
         }
         setObjectFieldValue(env, jtypeLib, "tlibAttr", "Lcom/argus/activex/TLIBATTR;", tlibAttr);

         env->SetObjectArrayElement(jtypeLibArray, i++, jtypeLib);

   	}

      return S_OK;

  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to TypeLib::readData(..)." );
      return E_FAIL;
  	}

}

