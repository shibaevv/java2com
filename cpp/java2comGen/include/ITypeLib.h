//---------------------------------------------------------------------------

#ifndef ITypeLibH
#define ITypeLibH
//---------------------------------------------------------------------------
#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class ITypeLib {
private:
   static ITypeLib * pTL;

   JNIEnv * env;
   ::ITypeLib * pTypeLib;

public:
   static ITypeLib * getInstance();

	ITypeLib(JNIEnv * env, ::ITypeLib * pTypeLib);
	~ITypeLib();

   HRESULT init(jobject obj);

   HRESULT addContainingTypeLib(::ITypeInfo * pTypeInfo, ::ITypeLib ** ppTypeLib);

};

}

#endif
