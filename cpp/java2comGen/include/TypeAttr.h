//---------------------------------------------------------------------------

#ifndef TypeAttrH
#define TypeAttrH

#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class TypeAttr {
private:
   JNIEnv * env;
   ::ITypeInfo * pTypeInfo;
   ::TYPEATTR * pTypeAttr;

   jstring guid;
   jint lcid;
   jint dwReserved;
   jint memidConstructor;
   jint memidDestructor;
   jstring lpstrSchema;
   jint cbSizeInstance;
   jshort typekind;
   jshort cFuncs;
   jshort cVars;
   jshort cImplTypes;
   jshort cbSizeVft;
   jshort cbAlignment;
   jshort wTypeFlags;
   jshort wMajorVerNum;
   jshort wMinorVerNum;

public:
	TypeAttr(JNIEnv * _env, ::ITypeInfo * _pTypeInfo, ::TYPEATTR * _pTypeAttr)
      : env(_env), pTypeInfo(_pTypeInfo), pTypeAttr(_pTypeAttr) {}
	~TypeAttr() {}

   HRESULT init(jobject obj);

   jshort getFunctionCount() { return cFuncs; }
   jshort getVariableCount() { return cVars; }

};

}

#endif
