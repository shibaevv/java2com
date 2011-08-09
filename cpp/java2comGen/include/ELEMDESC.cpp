//---------------------------------------------------------------------------

#include "ELEMDESC.h"
//---------------------------------------------------------------------------
#include "TYPEDESC.h"
#include "PARAMDESC.h"
#include "IDLDESC.h"

#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

/*
Includes the type description and process-transfer information for a variable,
a function, or a function parameter. It is defined as follows:

typedef struct tagELEMDESC{
   TYPEDESC tdesc;                  // Type of the element.
union {
        IDLDESC idldesc;        //Info for remoting the element
                                   //(backward compatibility)
        PARAMDESC paramdesc;    //info about the parameter
    };
} ELEMDESC, * LPELEMDESC;
   }  ELEMDESC;
*/

//---------------------------------------------------------------------------
HRESULT ELEMDESC::init(jobject obj) {

   HRESULT hr;

   ::TYPEDESC tdesc = pElemDesc->tdesc;
   // create new jobject
   jobject_auto jtdesc( env, "Lcom/argus/activex/TYPEDESC;" );
   hr = TYPEDESC(env, pTypeInfo, &tdesc).init(jtdesc);
	if ( FAILED(hr) )
	{
		return hr;
	}
   setObjectFieldValue(env, obj, "tdesc", "Lcom/argus/activex/TYPEDESC;", jtdesc);

   // union
   ::IDLDESC idldesc = pElemDesc->idldesc;
   jobject_auto jidldesc( env, "Lcom/argus/activex/IDLDESC;" );
   hr = IDLDESC(env, idldesc).init( jidldesc );
	if ( FAILED(hr) )
	{
		return hr;
	}
   setObjectFieldValue(env, obj, "idldesc", "Lcom/argus/activex/IDLDESC;", jidldesc);

   ::PARAMDESC paramdesc = pElemDesc->paramdesc;
   jobject_auto jparamdesc( env, "Lcom/argus/activex/PARAMDESC;" );
   hr = PARAMDESC(env, &paramdesc).init( jparamdesc );
	if ( FAILED(hr) )
	{
		return hr;
	}
   setObjectFieldValue(env, obj, "paramdesc", "Lcom/argus/activex/PARAMDESC;", jparamdesc);

   return S_OK;

}

