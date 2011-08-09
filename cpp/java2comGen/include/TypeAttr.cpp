//---------------------------------------------------------------------------

#include "TypeInfo.h"
#include "TypeAttr.h"
#include "TYPEDESC.h"
#include "IDLDESC.h"

#include "jobject_auto.h"
//#include "jobjectArray_auto.h"
#include "jni_utils.h"

#include <iostream>

using namespace argus;

/*
Contains attributes of an ITypeInfo, and is defined as follows:

typedef struct FARSTRUCT tagTYPEATTR {
   GUID guid;               // The GUID of the type information. 
   LCID lcid;               // Locale of member names and doc strings.
   unsigned long dwReserved;
   MEMBERID memidConstructor;   // ID of constructor, or MEMBERID_NIL if none.
   MEMBERID memidDestructor;   // ID of destructor, or MEMBERID_NIL if none.
   OLECHAR FAR* lpstrSchema;   // Reserved for future use.
   unsigned long cbSizeInstance;// The size of an instance of this type.
   TYPEKIND typekind;         // The kind of type this information describes.
   unsigned short cFuncs;      // Number of functions.
   unsigned short cVars;      // Number of variables/data members.
   unsigned short cImplTypes;   // Number of implemented interfaces.
   unsigned short cbSizeVft;   // The size of this type's VTBL.
   unsigned short cbAlignment;   // Byte alignment for an instance of this type.
   unsigned short wTypeFlags;
   unsigned short wMajorVerNum;   // Major version number.
   unsigned short wMinorVerNum;   // Minor version number.
   TYPEDESC tdescAlias;         // If TypeKind == TKIND_ALIAS, 
                        // specifies the type for which this type is an alias.
   IDLDESC idldescType;      // IDL attributes of the described type.
} TYPEATTR, FAR* LPTYPEATTR;
 

The cbAlignment field indicates how addresses are aligned.
A value of 0 indicates alignment on the 64K boundary;
1 indicates no special alignment.
For other values, n indicates aligned on byte n.
*/

//---------------------------------------------------------------------------
HRESULT TypeAttr::init(jobject obj) {

   HRESULT hr = E_FAIL;

   TYPEKIND typekind = pTypeAttr->typekind;
   WORD cImplTypes = pTypeAttr->cImplTypes;

   //If a type description describes a COM class,
   //it retrieves the type description of the implemented interface types.
   //For an interface, GetRefTypeOfImplType returns the type information
   //for inherited interfaces, if any exist.
   if (pTypeInfo != NULL && typekind == TKIND_COCLASS && cImplTypes > 0) {
      //Index of the implemented type whose handle is returned.
      //The valid range is 0 to the cImplTypes field in the TYPEATTR structure.
      unsigned int index = 0;
      //On return, points to a handle for the implemented interface (if any).
      //This handle can be passed to ITypeInfo::GetRefTypeInfo to get the type description.
      HREFTYPE hrefType = 0;
      hr = pTypeInfo->GetRefTypeOfImplType(index, &hrefType);
      if ( FAILED( hr ) ) {
         ThrowComException( env, DISP_E_EXCEPTION, "TypeAttr::newTypeAttr::GetRefTypeOfImplType(...) FAILED!" );
         return hr;
      }

   	::ITypeInfo * pTempInfo = NULL;
	   hr = pTypeInfo->GetRefTypeInfo(hrefType, &pTempInfo);
      if ( FAILED( hr ) ) {
         ThrowComException(env, E_FAIL, "TypeAttr::newTypeAttr::GetRefTypeInfo(...) FAILED.");
		   return hr;
      }
      TypeInfo tempInfo = TypeInfo(env, pTempInfo);
      BSTR baseClassName = tempInfo.getName();
      setFieldValue(env, obj, "baseClassName", NewString(env, baseClassName));

      ::TYPEATTR * pTempAttr = tempInfo.getTypeAttr();
      jshort typekind = pTempAttr->typekind;
      setFieldValue(env, obj, "baseClassTypekind", typekind);
   }

   wchar_t tmp[64];
   hr = StringFromGUID2( pTypeAttr->guid, tmp, 63 );
   if ( FAILED( hr ) ) {
      ThrowComException( env, DISP_E_EXCEPTION, "StringFromGUID2(...) FAILED!" );
      return hr;
   }
   guid = NewString(env, tmp);
   setFieldValue(env, obj, "guid", guid);
   setFieldValue(env, obj, "lcid", (jint) pTypeAttr->lcid);
   setFieldValue(env, obj, "memidConstructor", (jint) pTypeAttr->memidConstructor);
   setFieldValue(env, obj, "memidDestructor", (jint) pTypeAttr->memidDestructor);
   setFieldValue(env, obj, "lpstrSchema", NewString( env, pTypeAttr->lpstrSchema ));
   setFieldValue(env, obj, "cbSizeInstance", (jint) pTypeAttr->cbSizeInstance);
   setFieldValue(env, obj, "typekind", (jshort) typekind);
	cFuncs = pTypeAttr->cFuncs;
   setFieldValue(env, obj, "cFuncs", cFuncs);
	cVars = pTypeAttr->cVars;
   setFieldValue(env, obj, "cVars", cVars);
   setFieldValue(env, obj, "cImplTypes", (jshort) cImplTypes);
   setFieldValue(env, obj, "cbSizeVft", (jshort) pTypeAttr->cbSizeVft);
   setFieldValue(env, obj, "cbAlignment", (jshort) pTypeAttr->cbAlignment);
   setFieldValue(env, obj, "wTypeFlags", (jshort) pTypeAttr->wTypeFlags);
   setFieldValue(env, obj, "wMajorVerNum", (jshort) pTypeAttr->wMajorVerNum);
   setFieldValue(env, obj, "wMinorVerNum", (jshort) pTypeAttr->wMinorVerNum);

   /////////////////////////////////////////////////////////////////////////////
   // create/set new TYPEDESC for obj
   // TYPEDESC TYPEDESC = pTypeAttr->tdescAlias;
   /////////////////////////////////////////////////////////////////////////////
   ::TYPEDESC & tdesc = pTypeAttr->tdescAlias;
   jobject_auto jtdescAlias( env, "Lcom/argus/activex/TYPEDESC;" );
   hr = TYPEDESC(env, pTypeInfo, &tdesc).init(jtdescAlias);
	if ( FAILED(hr) )
	{
  		//pTypeInfo->ReleaseVarDesc(&elemdescFunc); // already throw Exception in init
		return hr;
	}
   setObjectFieldValue( env, obj, "tdescAlias", "Lcom/argus/activex/TYPEDESC;", jtdescAlias);

   /////////////////////////////////////////////////////////////////////////////
   // create/set new IDLDESC for obj
   // IDLDESC IDLDESC = pTypeAttr->idldescType;
   /////////////////////////////////////////////////////////////////////////////
   jobject_auto jidldescType( env, "Lcom/argus/activex/IDLDESC;" );
   hr = IDLDESC(env, pTypeAttr->idldescType).init( jidldescType );
	if ( FAILED(hr) )
	{
  		//pTypeInfo->ReleaseVarDesc(&elemdescFunc); // already throw Exception in init
		return hr;
	}
   setObjectFieldValue( env, obj, "idldescType", "Lcom/argus/activex/IDLDESC;", jidldescType);

   return S_OK;

}
