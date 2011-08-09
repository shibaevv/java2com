//---------------------------------------------------------------------------

#ifndef TYPEDESCH
#define TYPEDESCH

#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class TYPEDESC {
private:
   JNIEnv * env;
   ::ITypeInfo * pTypeInfo;
   ::TYPEDESC * ptdesc;

   ::ITypeInfo * getRefTypeInfo(::HREFTYPE hRefType);

public:
	TYPEDESC(JNIEnv * _env, ::ITypeInfo * _pTypeInfo, ::TYPEDESC * _ptdesc)
      : env(_env), pTypeInfo(_pTypeInfo), ptdesc(_ptdesc) {}
	~TYPEDESC() {}

   HRESULT init(jobject obj);

};

}

#endif
