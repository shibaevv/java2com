//---------------------------------------------------------------------------

#ifndef ARRAYDESCH
#define ARRAYDESCH
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class ARRAYDESC {
private:
   JNIEnv * env;
   ::ITypeInfo * pTypeInfo;
   ::ARRAYDESC * padesc;

   jobject tdescElem; // TYPEDESC
   jshort cDims;
   jobject rgbounds; // SAFEARRAYBOUND

public:
	ARRAYDESC(JNIEnv * _env, ::ITypeInfo * _pTypeInfo, ::ARRAYDESC * _padesc)
      : env(_env), pTypeInfo(_pTypeInfo), padesc(_padesc) {}
	~ARRAYDESC() {}

   HRESULT init(jobject obj);

};

}

#endif
