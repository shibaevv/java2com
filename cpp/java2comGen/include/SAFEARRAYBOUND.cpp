//---------------------------------------------------------------------------
#include "SAFEARRAYBOUND.h"

//#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

//---------------------------------------------------------------------------
HRESULT SAFEARRAYBOUND::init(jobject obj) {

   cElements = (jint) psabound->cElements;
   setFieldValue( env, obj, "cElements", cElements);

   lLbound = (jint) psabound->lLbound;
   setFieldValue( env, obj, "lLbound", lLbound);

   return S_OK;

}

