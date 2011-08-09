//---------------------------------------------------------------------------

#include "ARRAYDESC.h"
#include "TYPEDESC.h"
#include "SAFEARRAYBOUND.h"

#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

/*
Contained within the TYPEDESC, which describes the type of the array's elements,
and information about the array's dimensions. It is defined as follows:

typedef struct tagARRAYDESC{
   TYPEDESC tdescElem;            // Element type.
   unsigned short cDims;         // Dimension count.
   SAFEARRAYBOUND rgbounds[1];      // Variable length array containing
                           // one element for each dimension.
} ARRAYDESC;
*/

//---------------------------------------------------------------------------
HRESULT ARRAYDESC::init(jobject obj) {

   HRESULT hr = E_FAIL;
   
   /////////////////////////////////////////////////////////////////////////////
   // create/set new TYPEDESC
   /////////////////////////////////////////////////////////////////////////////
   ::TYPEDESC & tdesc = padesc->tdescElem;
   jobject_auto jtdescElem( env, "Lcom/argus/activex/TYPEDESC;" );
   hr = TYPEDESC(env, pTypeInfo, &tdesc).init(jtdescElem);
	if ( FAILED(hr) )
	{
  		//pTypeInfo->ReleaseVarDesc(&elemdescFunc); // already throw Exception in init
		return hr;
	}
   setObjectFieldValue( env, obj, "tdescElem", "Lcom/argus/activex/TYPEDESC;", jtdescElem);

   cDims = (jshort) padesc->cDims;
   setFieldValue( env, obj, "cDims", cDims);

   /////////////////////////////////////////////////////////////////////////////
   // create/set new SAFEARRAYBOUND
   /////////////////////////////////////////////////////////////////////////////
   ::SAFEARRAYBOUND rgbounds = padesc->rgbounds[0];
   jobject_auto jrgbounds( env, "Lcom/argus/activex/SAFEARRAYBOUND;" );
   hr = SAFEARRAYBOUND(env, &rgbounds).init(jrgbounds);
	if ( FAILED(hr) )
	{
  		//pTypeInfo->ReleaseVarDesc(&elemdescFunc); // already throw Exception in init
		return hr;
	}
   setObjectFieldValue( env, obj, "rgbounds", "Lcom/argus/activex/SAFEARRAYBOUND;", jrgbounds);

   return S_OK;

}


