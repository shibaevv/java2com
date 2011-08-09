//---------------------------------------------------------------------------

#ifndef IDLDESCH
#define IDLDESCH

#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class IDLDESC {
private:
   JNIEnv * env;
   ::IDLDESC & idldesc;

   jint dwReserved;
   jshort wIDLFlags;

public:
	IDLDESC(JNIEnv * _env, ::IDLDESC & _idldesc)
      : env(_env), idldesc(_idldesc) {}
	~IDLDESC() {}

   HRESULT init(jobject obj);
   
};

}

#endif
