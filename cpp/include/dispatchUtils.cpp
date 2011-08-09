//---------------------------------------------------------------------------
#include "stdafx.h"
#include "dispatchUtils.h"

const char version [] = "1.3";

HRESULT JNICALL GetRunningActiveObject
  (JNIEnv * env, jclass clazz, jstring clsid, IDispatch ** ppDisp)
{
   // jstring to char
   const char * utfChars = env->GetStringUTFChars( clsid, NULL );
   UBSTR lpsz(utfChars);
   env->ReleaseStringUTFChars(clsid, utfChars);

   // wchar_t to CLSID
   GUID guid;
   HRESULT hr = CLSIDFromString( lpsz, &guid );
   if ( FAILED( hr ) ) {
      //ThrowComException( env, hr, "CLSIDFromString(...) FAILED!" );
      //return hr;

      //WINOLEAPI CLSIDFromProgID (IN LPCOLESTR lpszProgID, OUT LPCLSID lpclsid);
      hr = CLSIDFromProgID( lpsz, &guid );
      if ( FAILED( hr ) ) {
         ThrowComException( env, hr, "CLSIDFromString/CLSIDFromProgID(...) FAILED!" );
         return hr;
      }

   }

   IUnknown * pItf = 0;
   hr = GetActiveObject( guid, 0, &pItf );
   if ( FAILED( hr ) ) {
      return hr;
   }

   //*ppDisp = 0;
   hr = pItf->QueryInterface(IID_IDispatch, (void**)ppDisp);
   pItf->Release();

   return hr;

}

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    GetJava2COMVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_argus_activex_DispatchUtils_GetJava2COMVersion
  (JNIEnv * env, jclass clazz)
{
   if ( env->ExceptionOccurred() )
      return NULL;
      
   try {
      return env->NewStringUTF( version );
   } catch (...) {
      ThrowComException( env, DISP_E_EXCEPTION, "FAILED to _GetJava2COMVersion." );
      return NULL;
   }

}

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    IsServerRunning
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_argus_activex_DispatchUtils_IsServerRunning
  (JNIEnv * env, jclass clazz, jstring clsid)
{
   if ( env->ExceptionOccurred() )
      return JNI_FALSE;

   try {
	/*
	   HRESULT hr;

	   // jstring to char
	   const char * utfChars = env->GetStringUTFChars( clsid, NULL );

	   // char to wchar_t
	   wchar_t lpsz[1024];
	   bool res = ustrncpy( lpsz, utfChars, 1024 );
	   env->ReleaseStringUTFChars( clsid, utfChars );
	   if ( !res ) {
	      ThrowComException( env, DISP_E_EXCEPTION, "CreateObject(...) ustrncpy(...) FAILED!" );
	      return JNI_FALSE;
	   }

	   IRunningObjectTable * prot = 0;
	   hr = GetRunningObjectTable( 0 , &prot );
		if ( FAILED(hr) ) {
	      ThrowComException( env, hr, "GetRunningObjectTable(...) FAILED!" );
	      return JNI_FALSE;
	   }

	   IBindCtx * pbc = 0;
	   hr = CreateBindCtx(0, &pbc);
		if ( FAILED(hr) ) {
	      ThrowComException( env, hr, "CreateBindCtx(...) FAILED!" );
	      return JNI_FALSE;
	   }

	   const OLECHAR * pwsz = lpsz;//OLESTR("clsid:000209FF-0000-0000-C000-000000000046:");
	   ULONG cchEaten;
	   IMoniker * pmnk = 0;
	//WINOLEAPI  MkParseDisplayName(IN LPBC pbc, IN LPCOLESTR szUserName,
	//                OUT ULONG FAR * pchEaten, OUT LPMONIKER FAR * ppmk);
	   hr = MkParseDisplayName(pbc, pwsz, &cchEaten, &pmnk);
		if ( FAILED(hr) ) {
	      ThrowComException( env, hr, "MkParseDisplayName(...) FAILED!" );
	      return JNI_FALSE;
	   }
	   cout << "cchEaten=" << cchEaten;
	   hr = prot->IsRunning(pmnk);

	   return hr == S_OK;
	//*/

	   IDispatch * pDisp = 0;
      HRESULT hr = GetRunningActiveObject(env, clazz, clsid, &pDisp);

	   if (FAILED(hr)) {
	      return JNI_FALSE;
      }

      pDisp->Release();
      return JNI_TRUE;

   } catch (...) {
      ThrowComException( env, DISP_E_EXCEPTION, "FAILED to IsServerRunning." );
	   return JNI_FALSE;
   }

}

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    GetActiveObject
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_DispatchUtils_GetActiveObject
  (JNIEnv * env, jclass clazz, jstring clsid)
{
   if ( env->ExceptionOccurred() )
      return 0;
      
   try {
	   IDispatch * pDisp = 0;
      HRESULT hr = GetRunningActiveObject(env, clazz, clsid, &pDisp);
	   if (SUCCEEDED(hr)) {
	      //cache(pDisp);  // ???
	      return (jint) pDisp;
	   }

	   // FAILED
      ThrowComException( env, hr, "FAILED to GetActiveObject." );
	   return 0;

   } catch (...) {
      ThrowComException( env, DISP_E_EXCEPTION, "FAILED to GetActiveObject." );
      return 0;
   }

}
/*
// does not work
HRESULT GetDispatch(REFCLSID rclsid, IDispatch ** pdisp)
{
   *pdisp = 0;
   IBindCtx *pbc = 0;
   HRESULT hr = CreateBindCtx(0, &pbc);
   if (SUCCEEDED(hr)) {
      ULONG cchEaten;
      IMoniker *pmk = 0;

      //HRESULT CreateClassMoniker([in] REFCLSID rclsid, [out] IMoniker **ppmk);
      hr = CreateClassMoniker( rclsid, &pmk );
      if (SUCCEEDED(hr)) {
         cout << "CreateClassMoniker OK!" << endl;

         IUnknown * pItf = 0;
         hr = pmk->BindToObject(pbc, 0, IID_IUnknown, (void**)&pItf);
         if (SUCCEEDED(hr)) {
            cout << "BindToObject IUnknown OK!" << endl;
            *pdisp = reinterpret_cast<IDispatch*>(pItf);
            (*pdisp)->AddRef();
            //hr = pItf->QueryInterface( rclsid, (void**)&pdisp );
         }

         // ask the moniker to find or create the object that it refers to
         //hr = pmk->BindToObject(pbc, 0, IID_IDispatch, (void**)&pdisp);
         // we now have a pointer to the desired object, so release
         // the moniker and the binding context

         pmk->Release();
      }
      pbc->Release();
   }
   return hr;

}
*/


//---------------------------------------------------------------------------
BOOL CALLBACK enumWindows(HWND hWnd, LPARAM lparam);

struct PARAM {
  long    left;
  long    top;
  long    right;
  long    bottom;
  HWND    hWnd;
};

BOOL CALLBACK enumWindows(HWND hWnd, LPARAM lparam) {
  static DWORD pid = GetCurrentProcessId();

  DWORD processId;
  //DWORD processId2 =
  GetWindowThreadProcessId(hWnd, &processId);
  if (pid == processId) {
    RECT r;
    if (GetWindowRect(hWnd, &r)) {
      PARAM * p = (PARAM *) lparam;
      if (p->left == r.left && p->top == r.top && p->right == r.right && p->bottom == r.bottom) {
        p->hWnd = hWnd;
        //std::cout << "HWND=" << hWnd << ", pid=" << pid << ", processId=" << processId << std::endl;
      }
    }
  }
  return true;
}

PARAM * createPARAM(JNIEnv * env, jobject component) {
    PARAM * param = new PARAM();

    jmethodID mid;
    jclass clazz = env->GetObjectClass(component);
    mid = env->GetMethodID(clazz, "getLocationOnScreen", "()Ljava/awt/Point;" );
    jobject location = env->CallObjectMethod(component, mid);
    mid = env->GetMethodID(clazz, "getSize", "()Ljava/awt/Dimension;" );
    jobject size = env->CallObjectMethod(component, mid);
    env->DeleteLocalRef(clazz);

    clazz = env->GetObjectClass(location);
    mid = env->GetMethodID(clazz, "getX", "()D");
    double x = env->CallDoubleMethod(location, mid);
    mid = env->GetMethodID(clazz, "getY", "()D");
    double y = env->CallDoubleMethod(location, mid);
    env->DeleteLocalRef(clazz);

    clazz = env->GetObjectClass(size);
    mid = env->GetMethodID(clazz, "getHeight", "()D" );
    double h = env->CallDoubleMethod(size, mid);
    mid = env->GetMethodID(clazz, "getWidth", "()D" );
    double w = env->CallDoubleMethod(size, mid);
    env->DeleteLocalRef(clazz);

    param->left = x;
    param->top = y;
    param->right = x + w;
    param->bottom = y + h;
    param->hWnd = 0;

    //std::cout << param->left << "," << param->top << "," << param->right << "," << param->bottom << std::endl;

    return param;
}
//---------------------------------------------------------------------------

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    GetHWND
 * Signature: (Ljava/awt/Component;)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_DispatchUtils_GetHWND
  (JNIEnv * env, jclass clazz, jobject canvas)
{
  try {
    jobject parent = canvas;
    jobject tmp = canvas;
    while (tmp != NULL) {
      jclass clazz = env->GetObjectClass(parent);
      jmethodID mid = env->GetMethodID(clazz, "getParent", "()Ljava/awt/Container;" );
      tmp = env->CallObjectMethod(tmp, mid);
      if (tmp != NULL) parent = tmp;
      env->DeleteLocalRef(clazz);
    }

    // find top level window
    PARAM * param = createPARAM(env, parent);
    if (EnumWindows(enumWindows, (LPARAM) param)) {
      HWND hWndParent = param->hWnd;
      delete param; param = 0;

      // find child window
      param = createPARAM(env, canvas);
      if (EnumChildWindows(hWndParent, enumWindows, (LPARAM) param)) {
        HWND hWndChild = param->hWnd;
        //cout << "Top level window: " << hWndParent << ", Child window: " << hWndChild << endl;
        delete param; param = 0;
        return (jint) hWndChild;
      }

    } else {
      ThrowComException( env, DISP_E_EXCEPTION, "FAILED to EnumWindows with Canvas Object." );
    }
    delete param; param = 0;

  } catch (...) {
    ThrowComException( env, DISP_E_EXCEPTION, "FAILED to CreateObjectCOM with Canvas Object." );
  }
  return 0;
}

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    ResizeControl
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_com_argus_activex_DispatchUtils_ResizeControl
  (JNIEnv * env, jclass clazz, jint hwnd, jint width, jint height)
{
    HWND hWnd = (HWND) hwnd;
    RECT rc;
    if (hWnd != NULL)
    {
        ::GetWindowRect(hWnd, &rc);
        HWND hwndChild = GetWindow(hWnd, GW_CHILD);
        if (::SetWindowPos(hwndChild,NULL,0,0,rc.right-rc.left,rc.bottom-rc.top,SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW|SWP_NOMOVE))
			;//std::cout << "ResizeControl(" << hwndChild << "," << width << "," << height << ")" << std::endl;
		else
			std::cerr << "FAILED ResizeControl()" << std::endl;
    }

}
