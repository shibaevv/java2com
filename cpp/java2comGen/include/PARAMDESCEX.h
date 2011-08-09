//---------------------------------------------------------------------------

#ifndef PARAMDESCEXH
#define PARAMDESCEXH
//---------------------------------------------------------------------------
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class PARAMDESCEX {
private:
   JNIEnv * env;
   ::PARAMDESCEX * pparamdescex;

public:
	PARAMDESCEX(JNIEnv * _env, ::PARAMDESCEX * _pparamdescex)
      : env(_env), pparamdescex(_pparamdescex) {}
	~PARAMDESCEX() {}

   HRESULT init(jobject obj);

};

}

#endif
