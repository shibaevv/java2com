//---------------------------------------------------------------------------

#include "FUNCDESC.h"
//---------------------------------------------------------------------------
//#include "TYPEDESC.h"
#include "ELEMDESC.h"

#include "jobject_auto.h"
#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

/*
Describes a function, and is defined as follows:

typedef struct tagFUNCDESC {
   MEMBERID memid;                  // Function member ID.
SCODE FAR *lprgscode;
ELEMDESC FAR *lprgelemdescParam;   
FUNCKIND funckind; // Specifies whether the function is virtual, static, or dispatch-only.
   INVOKEKIND invkind;      // Invocation kind. Indicates if this is a    
                           // property function, and if so, what kind.
   CALLCONV callconv;      // Specifies the function's calling convention.
   short cParams;         // Count of total number of parameters.
   short cParamsOpt;      // Count of optional parameters (detailed description follows).
   short oVft;      // For FUNC_VIRTUAL, specifies the offset in the VTBL.
   short cScodes;      // Count of permitted return values. 
   ELEMDESC elemdescFunc;   // Contains the return type of the function.
   WORD wFuncFlags;    // Definition of flags follows.
}   FUNCDESC;
 

The cParams field specifies the total number of required and optional parameters.

The cParamsOpt field specifies the form of optional parameters accepted by the function, as follows:

    * A value of 0 specifies that no optional arguments are supported.
    * A value of –1 specifies that the method's last parameter is a pointer to a safe array of variants.
      Any number of variant arguments greater than cParams –1 must be packaged by the caller into a safe
      array and passed as the final parameter. This array of optional parameters must be freed by the
      caller after control is returned from the call.
    * Any other number indicates that the last n parameters of the function are variants and do not need
    to be specified by the caller explicitly. The parameters left unspecified should be filled in by the
    compiler or interpreter as variants of type VT_ERROR with the value DISP_E_PARAMNOTFOUND.

For 16-bit systems (Macintosh), the fields cScodes and lprgscode store the count and the set of errors
that a function can return. If cScodes = –1, then the set of errors is unknown. If cScodes = –1, or if
cScodes = 0, then lprgscodeis undefined.
*/

//---------------------------------------------------------------------------
HRESULT FUNCDESC::init(jobject obj) {

   MEMBERID memid = pFuncDesc->memid;
   jshort cParams = pFuncDesc->cParams;
   BSTR rgBstrNames[128];
   unsigned int cMaxNames = 128;
   unsigned int cNames;
   //This method retrieves the variable with the specified member identifier,
   //or the name of the function and parameter names corresponding to the specified function identifier.
   HRESULT hr = pTypeInfo->GetNames(memid, rgBstrNames, cMaxNames, &cNames);
	if ( FAILED(hr) )
	{
		ThrowComException(env, hr, "GetNames failed.");
		return hr;
	}

   // create and set rgBstrNames (String array member)
   jobjectArray_auto jrgBstrNames( env, cNames, "Ljava/lang/String;");
   setObjectFieldValue(env, obj, "rgBstrNames", "[Ljava/lang/String;", jrgBstrNames);
	for ( unsigned int j = 0; j < cNames; j++ )
	{
      env->SetObjectArrayElement( jrgBstrNames, j, NewString(env, rgBstrNames[j]));
	}

   //setFieldValue(env, obj, "name", NewString(env, rgBstrNames[0]));
   setFieldValue(env, obj, "memid", (jint) memid);

   SCODE * lprgscode = pFuncDesc->lprgscode;
   if (lprgscode != NULL) setFieldValue(env, obj, "lprgscode", (jint) *lprgscode);
   setFieldValue(env, obj, "funckind", (jshort) pFuncDesc->funckind);
   setFieldValue(env, obj, "invkind", (jshort) pFuncDesc->invkind);
   setFieldValue(env, obj, "callconv", (jshort) pFuncDesc->callconv);
   setFieldValue(env, obj, "cParams", cParams);
   setFieldValue(env, obj, "cParamsOpt", (jshort) pFuncDesc->cParamsOpt);
   setFieldValue(env, obj, "oVft", (jshort) pFuncDesc->oVft);
   setFieldValue(env, obj, "cScodes", (jshort) pFuncDesc->cScodes);
   setFieldValue(env, obj, "wFuncFlags", (jshort) pFuncDesc->wFuncFlags);

   // create and set lprgelemdescParam (ELEMDESC array member)
   jobjectArray_auto jlprgelemdescParam( env, cParams, "Lcom/argus/activex/ELEMDESC;");
   setObjectFieldValue(env, obj, "lprgelemdescParam", "[Lcom/argus/activex/ELEMDESC;", jlprgelemdescParam);
	for ( int j = 0; j < cParams; j++ )
	{
      ::ELEMDESC param = pFuncDesc->lprgelemdescParam[j];
      jobject jparam = jlprgelemdescParam.NewObject();
      hr = ELEMDESC(env, pTypeInfo, &param).init( jparam );
		if ( FAILED(hr) )
		{
   		//pTypeInfo->ReleaseVarDesc(&param); // already throw Exception in newVARDESC
			return hr;
		}
      env->SetObjectArrayElement( jlprgelemdescParam, j, jparam);
	}

	::ELEMDESC elemdescFunc = pFuncDesc->elemdescFunc;
   // create new jobject
   jobject_auto jelemdescFunc( env, "Lcom/argus/activex/ELEMDESC;" );
   hr = ELEMDESC(env, pTypeInfo, &elemdescFunc).init( jelemdescFunc );
	if ( FAILED(hr) )
	{
  		//pTypeInfo->ReleaseVarDesc(&elemdescFunc); // already throw Exception in init
		return hr;
	}
   setObjectFieldValue(env, obj, "elemdescFunc", "Lcom/argus/activex/ELEMDESC;", jelemdescFunc);

   return S_OK;

}

