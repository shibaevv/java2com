//---------------------------------------------------------------------------

#ifndef PARAMDESCH
#define PARAMDESCH
//---------------------------------------------------------------------------
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class PARAMDESC {
private:
   JNIEnv * env;
   ::PARAMDESC * pParamDesc;

public:
	PARAMDESC(JNIEnv * _env, ::PARAMDESC * _pParamDesc)
      : env(_env), pParamDesc(_pParamDesc) {}
	~PARAMDESC() {}

   HRESULT init(jobject obj);

};

}

#endif
