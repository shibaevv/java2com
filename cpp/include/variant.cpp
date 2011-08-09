#include "stdafx.h"
#include "variant.h"

// Win32 support for Ole Automation
#include <wchar.h>
#include <string.h>
#include <atlbase.h>
#include <objbase.h>
#include <oleauto.h>
#include <olectl.h>

//extern "C"
//{

void variantClear(VARIANT *pV) {
   if (!pV) return;
   //std::cout << "VariantClear() " << pV << std::endl;
   ::VariantClear(pV);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_com_argus_activex_Variant_release
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   jclass clazz = env->GetObjectClass(_this);
   jfieldID jf = env->GetFieldID(clazz, VARIANT_FLD, "I");
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   // fix byref leak
   if (V_VT(v) & VT_BYREF) {       // is this a reference
      void * pMem = V_BSTRREF(v);    // get allocated memory
      if (pMem) {
         if (V_VT(v) == (VT_BYREF|VT_BSTR)) {
            BSTR  *pBstr = (BSTR*)pMem;
            if (*pBstr)
               SysFreeString(*pBstr);// release bstr
         }
         CoTaskMemFree(pMem);
      }
   }
   variantClear(v);
   //delete v;
   env->SetIntField(_this, jf, (unsigned int)0);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant::release method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_init
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return;
      
	try {
   jclass clazz = env->GetObjectClass(_this);
   jfieldID jf = env->GetFieldID( clazz, VARIANT_FLD, "I");
   VARIANT *v = new VARIANT();
   VariantInit(v);
   env->SetIntField(_this, jf, (unsigned int)v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant::init method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_VariantClear
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return;
      
	try {
  VARIANT *v = extractVariant(env, _this);
  if (v) variantClear(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant::variantClear method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_changeType
  (JNIEnv *env, jobject _this, jshort t)
{
   if ( env->ExceptionOccurred() )
      return;
      
	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   HRESULT hr = VariantChangeType(v, v, 0, t);
   if ( hr != S_OK )
      ThrowComException( env, hr, "VariantChangeType failed" );
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant::changeType method." );
  	}

}

JNIEXPORT jshort JNICALL Java_com_argus_activex_Variant_getvt
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;
      
	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;
   return (jshort)V_VT(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant::getvt method." );
      return NULL;
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_noParam
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return;
      
	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   V_VT(v) = VT_ERROR;
   V_ERROR(v) = DISP_E_PARAMNOTFOUND;
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT jboolean JNICALL Java_com_argus_activex_Variant_isNull
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;
      
	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return JNI_TRUE;
   if ((V_VT(v) & VT_ARRAY)) {
      // is it a null safearray
      if ((V_VT(v) & VT_BYREF))
         if (!V_ARRAYREF(v)) return JNI_TRUE;
      else
         if (!V_ARRAY(v)) return JNI_TRUE;
   }

   switch (V_VT(v)) {
      case VT_EMPTY:
      case VT_NULL:
      case VT_ERROR:
         return JNI_TRUE;
      // is it a null dispatch (Nothing in VB)
      case VT_DISPATCH:
         if (!V_DISPATCH(v)) return JNI_TRUE;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return JNI_FALSE;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
JNIEXPORT jobject JNICALL Java_com_argus_activex_Variant_toObject
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

  // not supported
  return NULL;
}

JNIEXPORT jbyte JNICALL Java_com_argus_activex_Variant_toByte
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if (FAILED(hr = VariantChangeType(v, v, 0, VT_UI1))) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   return (jbyte)V_UI1(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jshort JNICALL Java_com_argus_activex_Variant_toShort
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if (FAILED(hr = VariantChangeType(v, v, 0, VT_I2))) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   return (jshort)V_I2(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jint JNICALL Java_com_argus_activex_Variant_toInt
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if ( FAILED( hr = VariantChangeType(v, v, 0, VT_I4) ) ) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   return (jint)V_I4(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jdouble JNICALL Java_com_argus_activex_Variant_toDate
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if ( FAILED( hr = VariantChangeType(v, v, 0, VT_DATE) ) ) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   return (jdouble)V_DATE(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jboolean JNICALL Java_com_argus_activex_Variant_toBoolean
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if (FAILED(hr = VariantChangeType(v, v, 0, VT_BOOL))) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   return (jboolean)V_BOOL(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jfloat JNICALL Java_com_argus_activex_Variant_toFloat
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if (FAILED(hr = VariantChangeType(v, v, 0, VT_R4))) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   return (jfloat)V_R4(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jdouble JNICALL Java_com_argus_activex_Variant_toDouble
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if (FAILED(hr = VariantChangeType(v, v, 0, VT_R8))) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   return (jdouble)V_R8(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jlong JNICALL Java_com_argus_activex_Variant_toCurrency
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if (FAILED(hr = VariantChangeType(v, v, 0, VT_CY))) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   CY cy = V_CY(v);
   return (jlong)cy.int64;
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

/*
 * Class:     com_argus_activex_Variant
 * Method:    toDispatch
 * Signature: ()Lcom/argus/activex/Dispatch;
 */
JNIEXPORT jobject JNICALL Java_com_argus_activex_Variant_toDispatch
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
      VARIANT *v = extractVariant(env, _this);
      if (!v) return NULL;

      HRESULT hr = VariantChangeType(v, v, 0, VT_DISPATCH);
      if ( FAILED( hr ) ) {
         ThrowComException(env, hr, "VariantChangeType failed");
         return NULL;
      }
      jclass autoClass = env->FindClass("Lcom/argus/activex/Dispatch;");
      jmethodID autoCons = env->GetMethodID(autoClass, "<init>", "(Lcom/argus/activex/Variant;)V");
      // construct a Dispatch object to return
      //IDispatch * pDisp = V_DISPATCH(v);
      // I am copying the pointer to java
      //if (pDisp) pDisp->AddRef();
      jobject newAuto = env->NewObject(autoClass, autoCons, _this);//(jint)pDisp);
      return newAuto;
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jstring JNICALL Java_com_argus_activex_Variant_toString
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   switch (V_VT(v)) {
      case VT_EMPTY:
      case VT_NULL:
      case VT_ERROR:
         // causes VariantChangeType to bomb
         return env->NewStringUTF("null");
   }

   if ( FAILED( VariantChangeType(v, v, 0, VT_BSTR) ) ) {
      // cannot change type to a string
      return env->NewStringUTF("???");
   }

   BSTR bs = V_BSTR(v);
   return NewString( env, bs );
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jint JNICALL Java_com_argus_activex_Variant_toError
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   HRESULT hr;
   if (FAILED(hr = VariantChangeType(v, v, 0, VT_ERROR))) {
      ThrowComException(env, hr, "VariantChangeType failed");
      return NULL;
   }
   return (jint)V_ERROR(v);
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_com_argus_activex_Variant_getNull
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return;

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_getEmpty
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return;

}

JNIEXPORT jboolean JNICALL Java_com_argus_activex_Variant_getBoolean
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) == (VT_BOOL|VT_BYREF))
         return (jboolean)*V_BOOLREF(v);
   } else {
      if (V_VT(v) == (VT_BOOL))
         return (jboolean)V_BOOL(v);
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

   return NULL;
}

JNIEXPORT jbyte JNICALL Java_com_argus_activex_Variant_getByte
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) ==  (VT_UI1|VT_BYREF))
         return (jbyte)*V_UI1REF(v);
   } else {
      if (V_VT(v) ==  (VT_UI1))
         return (jbyte)V_UI1(v);
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jshort JNICALL Java_com_argus_activex_Variant_getShort
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) ==  (VT_I2|VT_BYREF))
         return (jshort)*V_I2REF(v);
   } else {
      if (V_VT(v) ==  VT_I2)
         return (jshort)V_I2(v);
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jint JNICALL Java_com_argus_activex_Variant_getInt
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) ==  (VT_I4|VT_BYREF))
         return (jint)*V_I4REF(v);
      if (V_VT(v) ==  (VT_DISPATCH|VT_BYREF))
         return (jint)*V_DISPATCHREF(v);
   } else {
      if (V_VT(v) ==  VT_I4)
         return (jint)V_I4(v);
      if (V_VT(v) ==  VT_DISPATCH)
         return (jint)V_DISPATCH(v);
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jfloat JNICALL Java_com_argus_activex_Variant_getFloat
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) ==  (VT_R4|VT_BYREF))
         return (jfloat)*V_R4REF(v);
   } else {
      if (V_VT(v) ==  (VT_R4))
         return (jfloat)V_R4(v);
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jdouble JNICALL Java_com_argus_activex_Variant_getDouble
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) ==  (VT_R8|VT_BYREF))
         return (jdouble)*V_R8REF(v);
   } else {
      if (V_VT(v) ==  VT_R8)
         return (jdouble)V_R8(v);
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jdouble JNICALL Java_com_argus_activex_Variant_getDate
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) ==  (VT_DATE|VT_BYREF))
         return (jdouble)*V_DATEREF(v);
   } else {
      if (V_VT(v) ==  VT_DATE)
         return (jdouble)V_DATE(v);
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jstring JNICALL Java_com_argus_activex_Variant_getString
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) == (VT_BSTR|VT_BYREF)) {
         BSTR *bs = V_BSTRREF(v);
         return NewString(env, *bs);
      }
   } else {
      if (V_VT(v) == VT_BSTR) {
         BSTR bs = V_BSTR(v);
         return NewString(env, bs);
      }
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jlong JNICALL Java_com_argus_activex_Variant_getCurrency
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) == (VT_CY|VT_BYREF)) {
         CY *cy = V_CYREF(v);
         jlong jl;
         memcpy(&jl, cy, 64);
         return jl;
      }
   } else {
      if (V_VT(v) == VT_CY) {
         CY cy = V_CY(v);
         jlong jl;
         memcpy(&jl, &cy, 64);
         return jl;
      }
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jint JNICALL Java_com_argus_activex_Variant_getError
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return NULL;

   if ( byRef ) {
      if (V_VT(v) == (VT_ERROR|VT_BYREF))
         return (jint)V_ERROR(v);
   } else {
      if (V_VT(v) == VT_ERROR)
         return (jint)V_ERROR(v);
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}
   return NULL;

}

JNIEXPORT jobject JNICALL Java_com_argus_activex_Variant_getObject
  (JNIEnv *env, jobject _this, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return NULL;

  return NULL;
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putNull
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   variantClear(v);
   V_VT(v) = VT_NULL;
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putEmpty
  (JNIEnv *env, jobject _this)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   variantClear(v);
   V_VT(v) = VT_EMPTY;
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putBoolean
  (JNIEnv *env, jobject _this, jboolean value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;
      //ThrowComException(env, -1, "putBoolean failed");

   variantClear(v);
   if ( byRef ) {
      VARIANT_BOOL *br = (VARIANT_BOOL *)CoTaskMemAlloc(sizeof(VARIANT_BOOL));
      *br = value ? VARIANT_TRUE : VARIANT_FALSE;
      V_VT(v) = VT_BOOL|VT_BYREF;
      V_BOOLREF(v) = br;
   } else {
      V_VT(v) = VT_BOOL;
      V_BOOL(v) = value == JNI_TRUE ? VARIANT_TRUE : VARIANT_FALSE;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putByte
  (JNIEnv *env, jobject _this, jbyte value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;
      //ThrowComException(env, -1, "putByte failed");

   variantClear(v);
   if ( byRef ) {
      unsigned char *br = (unsigned char *)CoTaskMemAlloc(sizeof(char));
      *br = value;
      V_VT(v) = VT_UI1|VT_BYREF;
      V_UI1REF(v) = br;
   } else {
      V_VT(v) = VT_UI1;
      V_UI1(v) = value;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putShort
  (JNIEnv *env, jobject _this, jshort value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   variantClear(v);
   if ( byRef ) {
      short *ps = (short *)CoTaskMemAlloc(sizeof(short));
      *ps = value;
      V_VT(v) = VT_I2|VT_BYREF;
      V_I2REF(v) = ps;
   } else {
      V_VT(v) = VT_I2;
      V_I2(v) = (short)value;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putInt
  (JNIEnv *env, jobject _this, jint value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   if ( byRef ) {
      variantClear(v);
      long *ps = (long *)CoTaskMemAlloc(sizeof(long));
      *ps = value;
      V_VT(v) = VT_I4|VT_BYREF;
      V_I4REF(v) = ps;
   } else {
      variantClear(v);
      V_VT(v) = VT_I4;
      V_I4(v) = (int)value;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putFloat
  (JNIEnv *env, jobject _this, jfloat value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   variantClear(v);
   if ( byRef ) {
      V_VT(v) = VT_R4;
      V_R4(v) = value;
   } else {
      float *pf = (float *)CoTaskMemAlloc(sizeof(float));
      *pf = value;
      V_VT(v) = VT_R4|VT_BYREF;
      V_R4REF(v) = pf;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putDouble
  (JNIEnv *env, jobject _this, jdouble value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   variantClear(v);
   if ( byRef ) {
      double *ps = (double *)CoTaskMemAlloc(sizeof(double));
      *ps = value;
      V_VT(v) = VT_R8|VT_BYREF;
      V_R8REF(v) = ps;
   } else {
      V_VT(v) = VT_R8;
      V_R8(v) = (double)value;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putDate
  (JNIEnv *env, jobject _this, jdouble value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   variantClear(v);
   if ( byRef ) {
      double *ps = (double *)CoTaskMemAlloc(sizeof(double));
      *ps = value;
      V_VT(v) = VT_DATE|VT_BYREF;
      V_DATEREF(v) = ps;
   } else {
      V_VT(v) = VT_DATE;
      V_DATE(v) = value;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putCurrency
  (JNIEnv *env, jobject _this, jlong value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   variantClear(v);
   if ( byRef ) {
      CY *pf = (CY *)CoTaskMemAlloc(sizeof(CY));
      memcpy(pf, &value, 64);
      V_VT(v) = VT_BYREF|VT_CY;
      V_CYREF(v) = pf;
   } else {

   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putString
  (JNIEnv *env, jobject _this, jstring value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;

   variantClear(v);

   // jstring to char
   const char * utfChars = env->GetStringUTFChars(value, NULL);
   CComBSTR bs((char*)utfChars);
   env->ReleaseStringUTFChars(value, utfChars);

   if ( byRef ) {
      BSTR *pbs = (BSTR *)CoTaskMemAlloc(sizeof(BSTR));
      bs.CopyTo(pbs);
      V_VT(v) = VT_BSTR|VT_BYREF;
      V_BSTRREF(v) = pbs;
   } else {
      V_VT(v) = VT_BSTR;
      V_BSTR(v) = bs.Copy();
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putError
  (JNIEnv *env, jobject _this, jint value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;
      //ThrowComException(env, -1, "putByte failed");

   variantClear(v);
   if ( byRef ) {
      long *ps = (long *)CoTaskMemAlloc(sizeof(long));
      *ps = value;
      V_VT(v) = VT_ERROR|VT_BYREF;
      V_ERRORREF(v) = ps;
   } else {
      V_VT(v) = VT_ERROR;
      V_ERROR(v) = (int)value;
   }
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

/*
 * Class:     com_argus_activex_Variant
 * Method:    putObject
 * Signature: (Ljava/lang/Object;Z)V
 */
JNIEXPORT void JNICALL Java_com_argus_activex_Variant_putDispatch
  (JNIEnv *env, jobject _this, jobject value, jboolean byRef)
{
   if ( env->ExceptionOccurred() )
      return;

	try {
   VARIANT *v = extractVariant(env, _this);
   if (!v) return;
      //ThrowComException(env, -1, "putDispatch failed");
//std::cout << "putDispatch: " << v << ", vt=" << V_VT(v) << std::endl;

   IDispatch *pDisp = extractDispatch(env, value);
   if (!pDisp) return;
      //ThrowComException(env, -1, "putDispatch failed");
//std::cout << "putDispatch: " << pDisp << std::endl;

   if ( byRef ) {
      V_VT(v) = VT_DISPATCH|VT_BYREF; // VT_USERDEFINED
      V_DISPATCHREF(v) = &pDisp;
   } else {
      V_VT(v) = VT_DISPATCH;
      V_DISPATCH(v) = pDisp;
   }
//std::cout << "putDispatch: " << v << ", vt=" << V_VT(v) << std::endl;
  	} catch (...) {
	   ThrowComException( env, E_FAIL, "FAILED to process Variant method." );
  	}

}

//} // extern "C"
