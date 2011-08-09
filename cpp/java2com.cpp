// java2com.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

//---------------------------------------------------------------------------
static const jint vmVersion = JNI_VERSION_1_2;

//------------------------------------------------------------------------------

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM * jvm, void * reserved)
{
   //std::cout << "JNI_OnLoad" << std::endl;

   JNIEnv * env = NULL;
   //jint res =
   jvm->GetEnv( (void**) &env, vmVersion );

   // retrieve license
   jclass clazz = env->FindClass("java/lang/System");
   jmethodID mid = env->GetStaticMethodID(
      clazz, "getProperty", "(Ljava/lang/String;)Ljava/lang/String;" );
   jstring license = (jstring) env->CallStaticObjectMethod(clazz, mid, env->NewStringUTF("java2com.license") );

   jboolean isCopy = JNI_FALSE;
   const char * pLicense = license == NULL ? "" : env->GetStringUTFChars(license, &isCopy );

   // create LicenseChecker
   LicenseChecker * pLC = Java2COMLicenseChecker::createInstance( pLicense );
   string * pDesc = pLC->find(pLicense);
   if (!pDesc) {
      pDesc = pLC->find("");
   }
   std::cout << *pDesc << std::endl;

   //env->ReleaseStringUTFChars(license, pLicense);

   return vmVersion;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM * jvm, void * reserved)
{
   //std::cout << "JNI_OnUnload" << std::endl;

   LicenseChecker * pLC = Java2COMLicenseChecker::getInstance();
   delete pLC;
}

boolean WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	// save instance handle
   Constants::hInstance = hinst;
   switch (reason) {
      case (DLL_PROCESS_ATTACH) :
         //std::cout << "HINSTANCE=" << hinst << ", " << "DLL_PROCESS_ATTACH" << std::endl;
         ::CoInitialize(0); // same as ::CoInitializeEx(0, COINIT_APARTMENTTHREADED);
		 //::CoInitializeEx(0, COINIT_MULTITHREADED);
         break;
      case (DLL_PROCESS_DETACH) :
         //std::cout << "HINSTANCE=" << hinst << ", " << "DLL_PROCESS_DETACH" << std::endl;
         ::CoUninitialize();
         break;
      case (DLL_THREAD_ATTACH) :
         //std::cout << "DLL_THREAD_ATTACH" << std::endl;
         ::CoInitialize(0); // same as ::CoInitializeEx(0, COINIT_APARTMENTTHREADED);
		 //::CoInitializeEx(0, COINIT_MULTITHREADED);
         break;
      case (DLL_THREAD_DETACH) :
         //std::cout << "DLL_THREAD_DETACH" << std::endl;
         ::CoUninitialize();
         break;
      default : ;
   }
   return true;//1;

}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD  reason, LPVOID lpReserved)
{
	// save instance handle 
   Constants::hModule = hModule;
   switch (reason) {
      case (DLL_PROCESS_ATTACH) :
         //std::cout << "HINSTANCE=" << hinst << ", " << "DLL_PROCESS_ATTACH" << std::endl;
         ::CoInitialize(0); // same as ::CoInitializeEx(0, COINIT_APARTMENTTHREADED);
		 //::CoInitializeEx(0, COINIT_MULTITHREADED);
         break;
      case (DLL_PROCESS_DETACH) :
         //std::cout << "HINSTANCE=" << hinst << ", " << "DLL_PROCESS_DETACH" << std::endl;
         ::CoUninitialize();
         break;
      case (DLL_THREAD_ATTACH) :
         //std::cout << "DLL_THREAD_ATTACH" << std::endl;
         ::CoInitialize(0); // same as ::CoInitializeEx(0, COINIT_APARTMENTTHREADED);
		 //::CoInitializeEx(0, COINIT_MULTITHREADED);
         break;
      case (DLL_THREAD_DETACH) :
         //std::cout << "DLL_THREAD_DETACH" << std::endl;
         ::CoUninitialize();
         break;
      default : ;
   }
    return TRUE;
}

