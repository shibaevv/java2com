//---------------------------------------------------------------------------
#include "PARAMDESC.h"
#include "PARAMDESCEX.h"

#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

/*
Contains information needed for transferring a structure element, parameter,
or function return value between processes. It is defined as follows:

typedef struct tagPARAMDESC {
   LPPARAMDESCEX pparamdescex;         //valid if PARAMFLAG_FHASDEFAULT
   USHORT wParamFlags;         // IN, OUT, etc
}  PARAMDESC;
 

The pparamdescex field contains a pointer to a PARAMDESCEX structure that describes
the default value for this parameter, if the PARAMFLAG_FHASDEFAULT bit of wParamFlags is set.
*/

//---------------------------------------------------------------------------
HRESULT PARAMDESC::init(jobject obj) {

   HRESULT hr = E_FAIL;
   
   jshort wParamFlags = pParamDesc->wParamFlags;
   setFieldValue(env, obj, "wParamFlags", wParamFlags);

   if ( wParamFlags & PARAMFLAG_FHASDEFAULT ) {
      ::PARAMDESCEX * pparamdescex = pParamDesc->pparamdescex;
      if (pparamdescex != NULL) {
         jobject_auto jpparamdescex( env, "Lcom/argus/activex/PARAMDESCEX;" );
         hr = PARAMDESCEX(env, pparamdescex).init( jpparamdescex );
      	if ( FAILED(hr) )
      	{
  		      //pTypeInfo->ReleaseVarDesc(&elemdescFunc); // already throw Exception in init
		      return hr;
      	}
         setObjectFieldValue(env, obj, "pparamdescex", "Lcom/argus/activex/PARAMDESCEX;", jpparamdescex);
      }
   }

   return S_OK;

}

