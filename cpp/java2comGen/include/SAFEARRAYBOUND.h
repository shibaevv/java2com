//---------------------------------------------------------------------------

#ifndef SAFEARRAYBOUNDH
#define SAFEARRAYBOUNDH
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class SAFEARRAYBOUND {
private:
   JNIEnv * env;
   ::SAFEARRAYBOUND * psabound;

   jint cElements;
   jint lLbound;

public:
	SAFEARRAYBOUND(JNIEnv * _env, ::SAFEARRAYBOUND * _psabound)
      : env(_env), psabound(_psabound) {}
	~SAFEARRAYBOUND() {}

   HRESULT init(jobject obj);

};

}

#endif
