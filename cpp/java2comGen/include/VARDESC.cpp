//---------------------------------------------------------------------------
#include "VARDESC.h"
//---------------------------------------------------------------------------
#include "TYPEDESC.h"
#include "ELEMDESC.h"

#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

/*
Describes a variable, constant, or data member. It is defined as follows:
typedef struct tagVARDESC {
   MEMBERID memid;
   OLECHAR FAR* lpstrSchema;   // Reserved for future use.
   union {
   unsigned long oInst;   // VAR_PERINSTANCE, the offset of this variable within the instance.
   VARIANT FAR* lpvarValue;   // VAR_CONST, the value of the constant.
   } UNION_NAME(u);
   ELEMDESC elemdescVar;   // Contains the variable type.
   unsigned short wVarFlags;   // Definition of flags follows
   VARKIND varkind;
} VARDESC
*/

//---------------------------------------------------------------------------
HRESULT VARDESC::init(jobject obj) {

   BSTR name;
	unsigned int nCount;
   MEMBERID memid = pVarDesc->memid;
	HRESULT hr = pTypeInfo->GetNames(memid, &name, 1, &nCount);
	if (FAILED(hr))
	{
		pTypeInfo->ReleaseVarDesc(pVarDesc);
		ThrowComException(env, hr, "GetNames failed.");
		return hr;
	}

   setFieldValue(env, obj, "name", NewString(env, name));
   setFieldValue(env, obj, "memid", (jint) memid);

   ::ELEMDESC elemdescVar = pVarDesc->elemdescVar;
   // create new jobject
   jobject_auto jelemdescVar( env, "Lcom/argus/activex/ELEMDESC;" );
   hr = ELEMDESC(env, pTypeInfo, &elemdescVar).init( jelemdescVar );
	if ( FAILED(hr) )
	{
  		//pTypeInfo->ReleaseVarDesc(&elemdescFunc); // already throw Exception in init
		return hr;
	}
   setObjectFieldValue(env, obj, "elemdescVar", "Lcom/argus/activex/ELEMDESC;", jelemdescVar);

   jshort wVarFlags = pVarDesc->wVarFlags;
   setFieldValue(env, obj, "wVarFlags", wVarFlags);

   jshort varkind = pVarDesc->varkind;
   setFieldValue(env, obj, "varkind", varkind);

	switch(varkind)
	{
	   case VAR_PERINSTANCE: {
         jint oInst = pVarDesc->oInst;
         setFieldValue(env, obj, "oInst", oInst);

			break;
      }
		case VAR_CONST: {
         // source
         ::VARIANT * lpvarValue = pVarDesc->lpvarValue;
         // destination
         jobject jlpvarValue = getObjectFieldValue(env, obj, "lpvarValue", "Lcom/argus/activex/Variant;");
         ::VARIANT * v = extractVariant(env, jlpvarValue);
         // copy
         VariantCopy(v, lpvarValue);

			break;

      }
		//case VAR_STATIC:
		//case VAR_DISPATCH:
		default:
			;
   }

   return S_OK;

}

