//---------------------------------------------------------------------------
#include "stdafx.h"
#include "TLIBATTR.h"

//#include "jni_utils.h"

//#include <iostream>

using namespace argus;

HRESULT TLIBATTR::init(jobject obj) {

   wchar_t guid[64];
   HRESULT hr = StringFromGUID2( pTLibAttr->guid, guid, 63 );
   if ( FAILED( hr ) ) {
      ThrowComException( env, DISP_E_EXCEPTION, "StringFromGUID2(...) FAILED!" );
      return hr;
   }
   setFieldValue(env, obj, "guid", NewString(env, guid));
   setFieldValue(env, obj, "lcid", (jint) pTLibAttr->lcid);
   setFieldValue(env, obj, "syskind", (jshort) pTLibAttr->syskind);
   setFieldValue(env, obj, "wMajorVerNum", (jshort) pTLibAttr->wMajorVerNum);
   setFieldValue(env, obj, "wMinorVerNum", (jshort) pTLibAttr->wMinorVerNum);
   setFieldValue(env, obj, "wLibFlags", (jshort) pTLibAttr->wLibFlags);

   return S_OK;

}

//---------------------------------------------------------------------------

