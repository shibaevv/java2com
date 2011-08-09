//---------------------------------------------------------------------------

#ifndef TypeInfoH
#define TypeInfoH

#include <jni.h>

#include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>

//---------------------------------------------------------------------------
namespace argus {

class TypeInfo {
private:
   JNIEnv * env;

   ::ITypeInfo * pTypeInfo;
   ::TYPEATTR * pTypeAttr;
   ::ITypeComp * pTypeComp;
   
   BSTR name;
   BSTR docString;
   DWORD helpContext;
   BSTR helpFile;

   HRESULT initTypeAttr();
   HRESULT initDocumentation();
   HRESULT initTypeComp();

public:
	TypeInfo(JNIEnv * _env, ::ITypeInfo * _pTypeInfo)
      : env(_env), pTypeInfo(_pTypeInfo), pTypeAttr(0), pTypeComp(0),
        name(0), docString(0), helpContext(0), helpFile(0) {}
     
	~TypeInfo();

   BSTR getName();
   ::TYPEATTR * getTypeAttr();

   HRESULT init(jobject obj);

};

}

#endif
