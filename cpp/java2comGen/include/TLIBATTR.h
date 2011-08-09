//---------------------------------------------------------------------------

#ifndef TLIBATTRH
#define TLIBATTRH
//---------------------------------------------------------------------------
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class TLIBATTR {
private:
   JNIEnv * env;
   ::ITypeLib * pTypeLib;
   ::TLIBATTR * pTLibAttr;

public:
	TLIBATTR(JNIEnv * _env, ::ITypeLib * _pTypeLib, ::TLIBATTR * _pTLibAttr)
      : env(_env), pTypeLib(_pTypeLib), pTLibAttr(_pTLibAttr) {}
	~TLIBATTR() {}

   HRESULT init(jobject obj);

};

}

#endif
