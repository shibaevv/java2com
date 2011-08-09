//---------------------------------------------------------------------------

#pragma hdrstop

#include "IDLDESC.h"

#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

using namespace argus;

//---------------------------------------------------------------------------
HRESULT IDLDESC::init(jobject obj) {

   wIDLFlags = (jshort) idldesc.wIDLFlags;
   setFieldValue(env, obj, "wIDLFlags", wIDLFlags);

   return S_OK;

}


