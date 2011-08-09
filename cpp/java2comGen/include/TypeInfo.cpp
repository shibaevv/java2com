//---------------------------------------------------------------------------

#include "TypeInfo.h"
#include "TypeAttr.h"
#include "FUNCDESC.h"
#include "VARDESC.h"

#include "jobject_auto.h"
#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

//---------------------------------------------------------------------------
TypeInfo::~TypeInfo() {
   // release resources
   if (pTypeAttr != NULL)
      pTypeInfo->ReleaseTypeAttr(pTypeAttr);
   //if (pTypeComp != NULL)
   //pTypeInfo->ReleaseTypeAttr(pTypeComp);
	pTypeInfo->Release();

   //::SysFreeString(name);
   //::SysFreeString(docString);
   //::SysFreeString(helpFile);

}

HRESULT TypeInfo::initTypeAttr() {
   if (pTypeAttr != NULL)
      return S_OK;

   HRESULT hr = pTypeInfo->GetTypeAttr(&pTypeAttr);
   if ( FAILED(hr) )
      ThrowComException(env, hr, "TypeInfo::GetTypeAttr failed.");

   return hr;
}

::TYPEATTR * TypeInfo::getTypeAttr() {
   if (pTypeAttr != NULL)
      return pTypeAttr;

   HRESULT hr = initTypeAttr();
   if ( FAILED(hr) )
      return NULL;
   return pTypeAttr;
}

HRESULT TypeInfo::initDocumentation() {
   HRESULT hr = initTypeAttr();
   if ( FAILED(hr) )
      return hr;

	hr = pTypeInfo->GetDocumentation(pTypeAttr->memidConstructor, &name, &docString, &helpContext, &helpFile);
	if ( FAILED(hr) ) {
		ThrowComException(env, hr, "GetDocumentation failed.");
	}
   return hr;
}

HRESULT TypeInfo::initTypeComp() {
	HRESULT hr = pTypeInfo->GetTypeComp(&pTypeComp);
	if ( FAILED(hr) ) {
		ThrowComException(env, hr, "GetTypeComp failed.");
	}
   return hr;
}

BSTR TypeInfo::getName() {
   if (name != NULL)
      return name;

   initDocumentation();
   return name;
}

/**
 * creates and init TypeInfo java object
 */
HRESULT TypeInfo::init(jobject obj) {
   HRESULT hr = initDocumentation();
   if ( FAILED(hr) )
      return hr;

   //WINOLEAUTAPI GetRecordInfoFromTypeInfo(ITypeInfo * pTypeInfo, IRecordInfo ** ppRecInfo);
   //::IRecordInfo * pRecInfo = NULL;
   //GetRecordInfoFromTypeInfo( pTypeInfo, &pRecInfo);

   setFieldValue(env, obj, "name", NewString(env, name));
   setFieldValue(env, obj, "docString", NewString(env, docString));
   setFieldValue(env, obj, "helpContext", (jint) helpContext);
   setFieldValue(env, obj, "helpFile", NewString(env, helpFile));


   /////////////////////////////////////////////////////////////////////////////
   // TypeAttr property
   /////////////////////////////////////////////////////////////////////////////
   jobject_auto jtypeAttr( env, "Lcom/argus/activex/TypeAttr;" );
   hr = TypeAttr(env, pTypeInfo, pTypeAttr).init( jtypeAttr );
	if ( FAILED(hr) )
	{
  		//pTypeInfo->ReleaseVarDesc(&elemdescFunc); // already throw Exception in init
		return hr;
	}
   setObjectFieldValue(env, obj, "typeAttr", "Lcom/argus/activex/TypeAttr;", jtypeAttr);


   /////////////////////////////////////////////////////////////////////////////
   // other properties
   /////////////////////////////////////////////////////////////////////////////
   // create and set funcDesc (FUNCDESC array member on TypeInfo)
   jshort cFuncs = getFieldValueShort( env, jtypeAttr, "cFuncs" );
   jshort cVars = getFieldValueShort( env, jtypeAttr, "cVars" );

   jobjectArray_auto funcDescArray( env, cFuncs, "Lcom/argus/activex/FUNCDESC;");
   setObjectFieldValue(env, obj, "funcDescArray", "[Lcom/argus/activex/FUNCDESC;", funcDescArray);
	for ( int i = 0; i < cFuncs; i++ )
	{
		::FUNCDESC* pFuncDesc;
		hr = pTypeInfo->GetFuncDesc(i, &pFuncDesc);
		if ( FAILED(hr) )
		{
			ThrowComException(env, hr, "GetFuncDesc failed.");
			return E_FAIL;
		}

      //METHODDATA Used to describe a method or property.
      //pTypeInfo->GetNames();

      // filter out IUnknown & IDispatch methods
      MEMBERID memid = pFuncDesc->memid;
      if (memid == 1610612736 || memid == 1610612737 || memid == 1610612738 ||
          memid == 1610678272 || memid == 1610678273 || memid == 1610678274 ||
          memid == 1610678275)
          continue;

      // create and set FUNCDESC element of array
      jobject_auto jfuncDesc( env, "Lcom/argus/activex/FUNCDESC;" );
      hr = FUNCDESC(env, pTypeInfo, pFuncDesc).init( jfuncDesc );
		if ( FAILED(hr) )
		{
   		pTypeInfo->ReleaseFuncDesc(pFuncDesc); // already throw Exception
			return hr;
		}
      env->SetObjectArrayElement(funcDescArray, i, jfuncDesc);

		pTypeInfo->ReleaseFuncDesc(pFuncDesc);
//std::cout << "--- DEBUG newFUNCDESC END ---" << jfuncDesc << std::endl;
	}


//*
   jobjectArray_auto varDescArray( env, cVars, "Lcom/argus/activex/VARDESC;");
   setObjectFieldValue(env, obj, "varDescArray", "[Lcom/argus/activex/VARDESC;", varDescArray);
	for (int i = 0; i < cVars; i++ )
	{
		::VARDESC* pVarDesc;
		hr = pTypeInfo->GetVarDesc(i, &pVarDesc);
		if ( FAILED(hr) )
		{
			ThrowComException(env, hr, "GetVarDesc failed.");
			return hr;
		}

      // create and set VARDESC element of array
      jobject_auto jvarDesc( env, "Lcom/argus/activex/VARDESC;" );
      hr = VARDESC(env, pTypeInfo, pVarDesc).init( jvarDesc );
		if ( FAILED(hr) )
		{
   		pTypeInfo->ReleaseVarDesc(pVarDesc); // already throw Exception in newVARDESC
			return hr;
		}
      env->SetObjectArrayElement(varDescArray, i, jvarDesc);

		pTypeInfo->ReleaseVarDesc(pVarDesc);

	}
//*/

   return S_OK;

}

