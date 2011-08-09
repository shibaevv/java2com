//---------------------------------------------------------------------------

#include "ITypeLib.h"
#include "TypeInfo.h"
#include "TYPEDESC.h"
#include "ARRAYDESC.h"

#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

/*
Describes the type of a variable, the return type of a function,
or the type of a function parameter. It is defined as follows:
typedef struct FARSTRUCT tagTYPEDESC {
    union {
      // VT_PTR - the pointed-at type
      struct FARSTRUCT tagTYPEDESC FAR* lptdesc;

      // VT_CARRAY
      struct FARSTRUCT tagARRAYDESC FAR* lpadesc;

      // VT_USERDEFINED - this is used to get a TypeInfo for the UDT
      HREFTYPE hreftype;

    }UNION_NAME(u);
    VARTYPE vt;
} TYPEDESC;

If the variable is VT_SAFEARRAY or VT_PTR, the union portion of the TYPEDESC
contains a pointer to a TYPEDESC that specifies the element type.
*/

//---------------------------------------------------------------------------
::ITypeInfo * TYPEDESC::getRefTypeInfo(::HREFTYPE hRefType) {
	::ITypeInfo * pTempInfo = NULL;
	HRESULT hr = pTypeInfo->GetRefTypeInfo(hRefType, &pTempInfo);
   return FAILED(hr) ? NULL : pTempInfo;
}

HRESULT TYPEDESC::init(jobject obj) {

   HRESULT hr = S_OK;
   //if (obj == 0) return S_OK;

//std::cout << "--- DEBUG START ---" << std::endl;
   jshort vt = (jshort) ptdesc->vt;
std::cout << "TYPEDESC vt=" << vt << "|" << ptdesc << "|" << obj << std::endl;
   setFieldValue(env, obj, "vt", vt);

   // *** union begin ***
   switch (vt) {
      case (VT_EMPTY) : {
//std::cerr << "\ttUnhandled: tdesc.vt=" << vt << std::endl;
         break;
      }
      case (VT_CARRAY) : {
//std::cout << "\tARRAYDESC: tdesc.vt=" << vt << std::endl;
         ::ARRAYDESC * lpadesc = ptdesc->lpadesc;
         if (lpadesc != NULL) {
            jobject_auto jlpadesc( env, "Lcom/argus/activex/ARRAYDESC;" );
            hr = ARRAYDESC(env, pTypeInfo, lpadesc).init( jlpadesc );    // ???
            setObjectFieldValue(env, obj, "adesc", "Lcom/argus/activex/ARRAYDESC;", jlpadesc);
         }
         break;
      }
      case (VT_USERDEFINED) : {
         jint hreftype = (jint) ptdesc->hreftype;
//std::cout << "\tTypeInfo for the UDT: tdesc.vt=" << vt << ", hreftype=" << hreftype << std::endl;
         // this is used to get a TypeInfo for the UDT
         setFieldValue(env, obj, "hreftype", hreftype);

         ::ITypeInfo * pTempInfo = getRefTypeInfo(hreftype);
         if (pTempInfo == NULL) {
//std::cerr << "TYPEDESC::GetRefTypeInfo failed for hreftype=" << hreftype << std::endl;
      	   //ThrowComException(env, E_FAIL, "TYPEDESC::GetRefTypeInfo failed.");
		      //return NULL;

         } else {
//std::cout << "TYPEDESC::GetRefTypeInfo succeded for hreftype=" << hreftype << ", pTempInfo=" << pTempInfo << std::endl;
            ::ITypeLib * pTypeLib = NULL;
            HRESULT hr = ITypeLib::getInstance()->addContainingTypeLib(pTempInfo, &pTypeLib);
            if ( FAILED( hr ) ) {
               break;
            }
            setFieldValue(env, obj, "pTypeLib", (jint) pTypeLib);

            TypeInfo tempInfo = TypeInfo(env, pTempInfo);
            BSTR name = tempInfo.getName();
            setFieldValue(env, obj, "name", NewString(env, name));

            ::TYPEATTR * pTempAttr = tempInfo.getTypeAttr();
            jshort typekind = pTempAttr->typekind;
            setFieldValue(env, obj, "typekind", typekind);
         }

         break;
      }
      case (257) : {
//std::cerr << "\ttUnhandled: tdesc.vt=" << vt << std::endl;
         break;
      }
      // pointer to a TYPEDESC that specifies the element type.
      case (VT_PTR) :
      case (VT_SAFEARRAY) : {
//std::cout << "\tTYPEDESC: tdesc.vt=" << vt << std::endl;
         ::TYPEDESC * lptdesc = ptdesc->lptdesc;
         if (lptdesc != NULL) {
            jobject_auto jlptdesc( env, "Lcom/argus/activex/TYPEDESC;" );
            hr = TYPEDESC(env, pTypeInfo, lptdesc).init(jlptdesc);
            if ( FAILED( hr ) ) {
               break;
            }
            setObjectFieldValue(env, obj, "tdesc", "Lcom/argus/activex/TYPEDESC;", jlptdesc);
         }
         break;
      }
      default:
         ::TYPEDESC * lptdesc = ptdesc->lptdesc;
         if (lptdesc != NULL) {
//std::cout << "\tdefault: tdesc.vt=" << vt << ", ptdesc->lptdesc=" << lptdesc << std::endl;
            jobject_auto jlptdesc( env, "Lcom/argus/activex/TYPEDESC;" );
            hr = TYPEDESC(env, pTypeInfo, lptdesc).init(jlptdesc);
            if ( FAILED( hr ) ) {
               break;
            }
            setObjectFieldValue(env, obj, "tdesc", "Lcom/argus/activex/TYPEDESC;", jlptdesc);
         }
   }
   // *** union end ***

   return hr;

}


