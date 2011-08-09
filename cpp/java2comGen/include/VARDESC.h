//---------------------------------------------------------------------------

#ifndef VARDESCH
#define VARDESCH
//---------------------------------------------------------------------------
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class VARDESC {
private:
   JNIEnv * env;
   ::ITypeInfo * pTypeInfo;
   ::VARDESC * pVarDesc;

public:
	VARDESC(JNIEnv * _env, ::ITypeInfo * _pTypeInfo, ::VARDESC * _pVarDesc)
      : env(_env), pTypeInfo(_pTypeInfo), pVarDesc(_pVarDesc) {}
	~VARDESC() {}

   HRESULT init(jobject obj);

};

}

#endif
