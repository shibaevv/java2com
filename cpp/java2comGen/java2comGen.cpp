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
   return vmVersion;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM * jvm, void * reserved)
{
   //std::cout << "JNI_OnUnload" << std::endl;
}

boolean WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
   Constants::hInstance = hinst;
   switch (reason) {
      case (DLL_PROCESS_ATTACH) :
         //std::cout << "HINSTANCE=" << hinst << ", " << "DLL_PROCESS_ATTACH" << std::endl;
         ::CoInitialize(NULL);
         break;
      case (DLL_PROCESS_DETACH) :
         //std::cout << "HINSTANCE=" << hinst << ", " << "DLL_PROCESS_DETACH" << std::endl;
         ::CoUninitialize();
         break;
      case (DLL_THREAD_ATTACH) :
         //std::cout << "DLL_THREAD_ATTACH" << std::endl;
         ::CoInitialize(NULL);
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
   Constants::hModule = hModule;
   switch (reason) {
      case (DLL_PROCESS_ATTACH) :
         //std::cout << "HINSTANCE=" << hinst << ", " << "DLL_PROCESS_ATTACH" << std::endl;
         ::CoInitialize(NULL);
         break;
      case (DLL_PROCESS_DETACH) :
         //std::cout << "HINSTANCE=" << hinst << ", " << "DLL_PROCESS_DETACH" << std::endl;
         ::CoUninitialize();
         break;
      case (DLL_THREAD_ATTACH) :
         //std::cout << "DLL_THREAD_ATTACH" << std::endl;
         ::CoInitialize(NULL);
         break;
      case (DLL_THREAD_DETACH) :
         //std::cout << "DLL_THREAD_DETACH" << std::endl;
         ::CoUninitialize();
         break;
      default : ;
   }
    return TRUE;
}
