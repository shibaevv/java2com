//---------------------------------------------------------------------------
#include "PARAMDESCEX.h"

//#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

/*
Contains information about the default value of the parameter. It is defined as follows:

typedef struct FARSTRUCT tagPARAMDESCEX {
   VARIANT *cByte;                     // size of this struct
   VARIANTARG varDefaultValue;         // default value of this parameter
} PARAMDESCEX
*/

//---------------------------------------------------------------------------
HRESULT PARAMDESCEX::init(jobject obj) {

   jint cBytes = pparamdescex->cBytes;
   setFieldValue(env, obj, "cBytes", cBytes);

   // source
   ::VARIANT varDefaultValue = pparamdescex->varDefaultValue;
   // destination
   jobject jvarDefaultValue = getObjectFieldValue(env, obj, "varDefaultValue", "Lcom/argus/activex/Variant;");
   ::VARIANT *v = extractVariant(env, jvarDefaultValue);
   // copy
   VariantCopy(v, &varDefaultValue);

   return S_OK;

}

