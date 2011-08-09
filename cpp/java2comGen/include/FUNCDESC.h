//---------------------------------------------------------------------------

#ifndef FUNCDESCH
#define FUNCDESCH
//---------------------------------------------------------------------------
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class FUNCDESC {
private:
   JNIEnv * env;
   ::ITypeInfo * pTypeInfo;
   ::FUNCDESC * pFuncDesc;
   
public:
	FUNCDESC(JNIEnv * _env, ::ITypeInfo * _pTypeInfo, ::FUNCDESC * _pFuncDesc)
      : env(_env), pTypeInfo(_pTypeInfo), pFuncDesc(_pFuncDesc) {}
	~FUNCDESC() {}

   HRESULT init(jobject obj);
   
};

}

#endif
