//---------------------------------------------------------------------------

#ifndef ELEMDESCH
#define ELEMDESCH
//---------------------------------------------------------------------------
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class ELEMDESC {
private:
   JNIEnv * env;
   ::ITypeInfo * pTypeInfo;
   ::ELEMDESC * pElemDesc;

public:
	ELEMDESC(JNIEnv * _env, ::ITypeInfo * _pTypeInfo, ::ELEMDESC * _pElemDesc)
      : env(_env), pTypeInfo(_pTypeInfo), pElemDesc(_pElemDesc) {}
	~ELEMDESC() {}

   HRESULT init(jobject obj);

};

}

#endif
