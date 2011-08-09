//---------------------------------------------------------------------------
#include "stdafx.h"
#include "dispatch.h"

#include <process.h>
// Includes for ATL
#pragma comment(lib,"atl.lib")
#include <atldef.h>
#define _ATL_DLL_IMPL
#include <atliface.h>
#include <atlbase.h>
#include <exdisp.h>

// standard MTA lifetime management helpers
HANDLE g_heventDone = ::CreateEvent(0, TRUE, FALSE, 0);

// Structure for CreateControl Thread Parameters.
typedef struct {
	CLSID clsid;
	jint id; // temp seq id
	HWND hCanvasWnd;
	HWND hControlWnd;
} CreateControlParam;

// Helper functions (CreateControl).
VOID CreateControl(CreateControlParam *);
static void WINAPIV StartCreateControlThread(LPVOID);

class InvokeParam  
{
private:
	bool ownDispatchHWND;
	JNIEnv * pEnv;
	JavaVM * pJavaVM;
public:
	// from caller
	DispatchHWND * pDispatchHWND;
	int nParamCount;
	// from IDispatch::Invoke()
    DISPID dispIdMember; // [in]
    REFIID riid;   // [in]
    LCID lcid;   // [in]
    WORD wFlags;      // [in]
    DISPPARAMS * pDispParams;  // [out][in] __RPC_FAR 
    VARIANT * const pVarResult;  // [out] __RPC_FAR 
    EXCEPINFO * pExcepInfo;  // [out] __RPC_FAR 
    UINT nArgErr;   // [out] __RPC_FAR 

public:
	InvokeParam(JNIEnv * pEnv, IDispatch * pDispatch, VARIANT * pVarResult)
	  : pEnv(pEnv), pDispatchHWND(new DispatchHWND(pDispatch, 0, 0)), ownDispatchHWND(true)
	    , nParamCount(0), dispIdMember(0)
		, riid(IID_NULL), lcid(LOCALE_SYSTEM_DEFAULT)
		, wFlags(0), pDispParams(new DISPPARAMS()), pVarResult(pVarResult)
		, pExcepInfo(new EXCEPINFO()), nArgErr((UINT)-1)
	{
		jint res = pEnv->GetJavaVM(&pJavaVM);
	}

	InvokeParam(JNIEnv * pEnv, DispatchHWND * pDispatchHWND, VARIANT * pVarResult)
	  : pEnv(pEnv), pDispatchHWND(pDispatchHWND), ownDispatchHWND(false) 
	    , nParamCount(0), dispIdMember(0)
		, riid(IID_NULL), lcid(LOCALE_SYSTEM_DEFAULT)
		, wFlags(0), pDispParams(new DISPPARAMS()), pVarResult(pVarResult)
		, pExcepInfo(new EXCEPINFO()), nArgErr((UINT)-1)
	{
		jint res = pEnv->GetJavaVM(&pJavaVM);
	}

	~InvokeParam();

	// TODO: use auto-pointer (to detach)
	JNIEnv * attachJNIEnv() const {
		// Attach this thread.
		JNIEnv * pCurThreadEnv = NULL;
		pJavaVM->AttachCurrentThread((void **)&pCurThreadEnv, NULL);
		return pCurThreadEnv;
	}
	jint detachJNIEnv(JNIEnv * env) const {
		return env == pEnv ? 0 : pJavaVM->DetachCurrentThread();
	}

};
InvokeParam::~InvokeParam() {
	if (ownDispatchHWND) {
		//cout << "Deleteing InvokeParam: " << this << endl;
		delete pDispatchHWND; pDispatchHWND = NULL;
	}
    delete pDispParams; pDispParams = NULL;
	delete pExcepInfo; pExcepInfo = NULL;
}

// Helper functions (Invoke).
HRESULT Invoke(InvokeParam *);
static HRESULT WINAPIV StartInvoke(InvokeParam *);

// store created dispatch data in special container (Singleton)
static jint dispatchId = 0;
// internal message id
static const UINT WM_INVOKE = WM_USER + 19630;

// TODO: use map instead of singleton
//static IDispatch * pCanvasDispatch = NULL;

/*
 * Class:     com_argus_activex_Dispatch
 * Method:    CreateObjectCOM
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_Dispatch_CreateObjectCOM
  (JNIEnv * env, jobject obj, jstring clsid, jint clsctx)
{
   if ( env->ExceptionOccurred() )
      return 0;

   try {
	   HRESULT hr;

	   // jstring to char
	   const char * utfChars = env->GetStringUTFChars( clsid, NULL );
       UBSTR lpsz(utfChars);
	   env->ReleaseStringUTFChars(clsid, utfChars);

	   // wchar_t to CLSID
	   GUID guid;
      //WINOLEAPI CLSIDFromString(IN LPOLESTR lpsz, OUT LPCLSID pclsid);
	   hr = CLSIDFromString( lpsz, &guid );
	   if ( FAILED( hr ) ) {
	      //ThrowComException( env, hr, "CLSIDFromString(...) FAILED!" );
	      //return 0;

         //WINOLEAPI CLSIDFromProgID (IN LPCOLESTR lpszProgID, OUT LPCLSID lpclsid);
	      hr = CLSIDFromProgID( lpsz, &guid );
	      if ( FAILED( hr ) ) {
	         ThrowComException( env, hr, "CLSIDFromString/CLSIDFromProgID(...) FAILED!" );
	         return 0;
	      }
	   }

	   // CLSCTX_LOCAL_SERVER, CLSCTX_ALL
		// pointer to the IDispatch interface
		IDispatch * pDisp = 0;

	/*
	   MULTI_QI mqi = { &IID_IDispatch, 0, 0 };
	   hr = CoCreateInstanceEx(
	      guid,
	      0,
	      clsctx,
	      0,
	      1,
	      &mqi );
		if ( FAILED(hr) ) {
	      ThrowComException( env, hr, "CoCreateInstanceEx(...) FAILED!" );
	      return 0;
	   }
	   pDisp = reinterpret_cast<IDispatch*>(mqi.pItf);
	//*/

	//*
		hr = CoCreateInstance(
	      guid,
	      NULL,
	      clsctx,
	      IID_IDispatch,
	      (void**)(&pDisp) );
		if ( FAILED(hr) ) {
	      ThrowComException( env, hr, "CoCreateInstance(...) FAILED!" );
	      return 0;
	   }
	//*/

	//cout << "CoAddRefServerProcess()=" << CoAddRefServerProcess() << endl;

	   if (SUCCEEDED(hr)) {
         //pDisp->AddRef();
	      return (jint) pDisp;
	   }

	   ThrowComException( env, hr, "Dispatch::CreateObjectCOM(...) FAILED!" );
	   return 0;

   } catch (...) {
      ThrowComException( env, DISP_E_EXCEPTION, "FAILED to CreateObjectCOM." );
	   return 0;
   }

}

/*
 * Class:     com_argus_activex_Dispatch
 * Method:    CreateObjectDCOM
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_Dispatch_CreateObjectDCOM
  (JNIEnv * env, jobject obj, jstring server, jstring clsid, jint clsctx)
{
   if ( env->ExceptionOccurred() )
      return 0;

   jint id = 0;

   return id;
}

/*
 * Class:     com_argus_activex_Dispatch
 * Method:    CreateObjectCanvas
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_Dispatch_CreateObjectCanvas
  (JNIEnv * env, jobject obj, jstring clsid, jint hCanvasWnd)
{
   if ( env->ExceptionOccurred() )
      return 0;

	//std::cout << "Creating Component for hCanvasWnd: " << (HWND) hCanvasWnd << std::endl;
	try {
		CreateControlParam * pCreateParam = new CreateControlParam();
		// Fill up the params.
		pCreateParam->hCanvasWnd = (HWND) hCanvasWnd;
        pCreateParam->hControlWnd = NULL;
		// temp sequence id (will be used to retrieve real pDispatch on Invoke)
        pCreateParam->id = ++dispatchId;

		// jstring to char
		const char * utfChars = env->GetStringUTFChars( clsid, NULL );
		UBSTR lpsz(utfChars);
		env->ReleaseStringUTFChars(clsid, utfChars);
		// wchar_t to CLSID
		HRESULT hr = CLSIDFromString(lpsz, &pCreateParam->clsid);
		if (FAILED(hr)) {
	      ThrowComException( env, hr, "CLSIDFromString(...) FAILED!" );
		  delete pCreateParam;
	      return 0;
		}

		// Launch the Thread (pParam will be deleted in StartCreateControlThread).
		_beginthread(StartCreateControlThread, 0, pCreateParam);
		
		::WaitForSingleObject(g_heventDone, INFINITE);
		::ResetEvent(g_heventDone);

		// sequence id
		return pCreateParam->id;

	} catch (...) {
		ThrowComException( env, DISP_E_EXCEPTION, "FAILED to CreateObjectCOM for HWND." );
		return 0;
	}

}

// Thread for creating the control 
/*
Message structure
typedef struct tagMSG {
    HWND        hwnd;
    UINT        message;
    WPARAM      wParam;
    LPARAM      lParam;
    DWORD       time;
    POINT       pt;
#ifdef _MAC
    DWORD       lPrivate;
#endif
} MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;
 */
void WINAPIV StartCreateControlThread(LPVOID lpVoid)
{
    //::CoInitialize(0);
	::CoInitializeEx(0, COINIT_MULTITHREADED);
	
	// destroy CreateControlParam here !!!
	CreateControlParam * pCreateParam = (CreateControlParam *)lpVoid;
    CreateControl(pCreateParam);

	// replacement to SendMessage			
	::SetEvent(g_heventDone);

	HWND hCanvasWnd = pCreateParam->hCanvasWnd;
	HWND hControlWnd = pCreateParam->hControlWnd;
    delete pCreateParam; pCreateParam = NULL;

	//cout << hCanvasWnd << ":" << hControlWnd << endl;

    MSG msg;
	BOOL bRet;
    // Windows message loop.
    while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
		if (bRet == -1)
		{
			// handle the error and possibly exit
			cerr << "handle the error and possibly exit" << endl;
		}

		//cout << "GetMessage msg.message=" << msg.message << " for msg.hwnd=" << msg.hwnd << endl;
        //TranslateMessage(&msg);
	    
		switch (msg.message)
		{
			case WM_INVOKE:
			{
				InvokeParam * pInvokeParam = (InvokeParam *) msg.lParam;
				
				HRESULT hr = Invoke(pInvokeParam);
				//cout << hr << "=Invoke(..) GetMessage WM_INVOKE msg.hwnd=" << msg.hwnd << ", pInvokeParam=" << pInvokeParam << endl;
				if (SUCCEEDED(hr) && InSendMessage()) 
					ReplyMessage((long) pInvokeParam->pVarResult); 
			
				// replacement to SendMessage			
				::SetEvent(g_heventDone);

				break;
			}
		}
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	
	::CoUninitialize();
}

// Creates ActiveX control
VOID CreateControl(CreateControlParam *pCreateParam)
{
    AtlAxWinInit();

	//WINOLEAPI ProgIDFromCLSID (REFCLSID clsid, LPOLESTR FAR* lplpszProgID);
	LPOLESTR lpOleStr;
	HRESULT hr = ProgIDFromCLSID(pCreateParam->clsid, &lpOleStr);
	if ( FAILED( hr ) ) {
		//TODO: throw
		//ThrowComException( env, hr, "ProgIDFromCLSID(...) FAILED!" );
		cerr << "ProgIDFromCLSID(...) FAILED!" <<  hex << hr << endl;
		return;
	}

	//bool ustrncpy( char * p1, const wchar_t * p2, size_t c = INT_MAX );
	char progID[1024];
	ustrncpy(progID, lpOleStr);
	cout << "CreateControl progID: " << progID << endl;

    // In the 2nd Param you can use ProgID or UUID of any activex control.
    HWND hControlWnd = ::CreateWindow(
         "AtlAxWin",              // See RegisterClass() call.
         progID,				  // Text for window title bar.
		 WS_CHILD|WS_VISIBLE,     // Window style.
         CW_USEDEFAULT,           // Default horizontal position.
         CW_USEDEFAULT,           // Default vertical position.
         CW_USEDEFAULT,           // Default width.
         CW_USEDEFAULT,           // Default height.
         pCreateParam->hCanvasWnd,// NULL, Overlapped windows have no parent.
         NULL,                    // Use the window class menu.
		 ::GetModuleHandle(NULL), // This instance owns this window.
         NULL);                   // Pointer not needed.

	//cout << "Created hControlWnd=" << hControlWnd 
	//	 << " for hCanvasWnd=" << pCreateParam->hCanvasWnd << endl;
    // If window could not be created, return "failure"
    if (!hControlWnd)
       return;

    // Show the window and paint its contents.
    //ShowWindow(hControlWnd, nCmdShow); 
    //UpdateWindow(hControlWnd); 
 
    IUnknown *pUnk = NULL;
    AtlAxGetControl(hControlWnd, &pUnk);
    //std::cout << "Created pUnk: " << pUnk << std::endl;
    if (!pUnk)
		return;
	pCreateParam->hControlWnd = hControlWnd;

/*
    // get an interface to set the URL.
    CComPtr<IWebBrowser2> spBrowser;
    pUnk->QueryInterface(IID_IWebBrowser2, (void**)&spBrowser);
    if (spBrowser)
    {
		char szURL[] = "http://localhost/";
        CComVariant ve;
        CComVariant vurl(szURL);
#pragma warning(disable: 4310) // cast truncates constant value
        spBrowser->put_Visible(VARIANT_TRUE);
#pragma warning(default: 4310) // cast truncates constant value
        spBrowser->Navigate2(&vurl, &ve, &ve, &ve, &ve);
    }
//*/

	// get an interface.
	IDispatch * pCanvasDispatch = NULL;
    pUnk->QueryInterface(IID_IDispatch, (void**) &pCanvasDispatch);

	// store in temp map
	DispatchHWND * pDispatchHWND = new DispatchHWND(
		pCanvasDispatch, pCreateParam->hCanvasWnd, hControlWnd);
	IDispatchContainer::getInstance()->insert(pCreateParam->id, pDispatchHWND);
    //cout << "Created id=pCanvasDispatch: " << pCreateParam->id << "=" << pCanvasDispatch << std::endl;

    //HookControlWndProc();
    //if (IsWindowVisible(hControlWnd))
    //  ShowWindow(hControlWnd, SW_HIDE);
	
}

////////////////////////////////////////////////////////////////////////////////
//       USES Variant.java
////////////////////////////////////////////////////////////////////////////////
/*
 * Class:     com_argus_activex_Dispatch
 * Method:    Invoke
 * Signature: (I[Lcom/argus/activex/Variant;ISLcom/argus/activex/Variant;Z)V
 */
JNIEXPORT void JNICALL Java_com_argus_activex_Dispatch_Invoke
  (JNIEnv * env, jobject obj,
   jint id,
   jobjectArray params,
   jint dispMethodID,
   jshort wInvokeFlag,
   jobject output)
{
	if ( env->ExceptionOccurred() )
		return;

	try {
		jint pDispId = extractPDispatch(env, obj);
		if (!pDispId) {
			ThrowComException( env, DISP_E_EXCEPTION, "IDispatch_Invoke(...), could not find IDispatch" );
			return;
		}

		// prepare a new return value
		// get the new return VARIANT from the output
		VARIANT * pVarResult = output == 0 ? 0 : extractVariant(env, output);
		if (pVarResult != 0) ::VariantInit(pVarResult);

		InvokeParam * pInvokeParam;
		DispatchHWND * pDispatchHWND = IDispatchContainer::getInstance()->find(pDispId);
		if (pDispatchHWND) {
			pInvokeParam = new InvokeParam(env, pDispatchHWND, pVarResult);
		} else {
			pInvokeParam = new InvokeParam(env, extractDispatch(env, obj), pVarResult);
		}

		int nParamCount = getArrayLength(env, params);

		//The arguments are passed in the array rgvarg[ ],
		//with the number of arguments passed in cArgs.
		//The arguments in the array should be placed from last to first,
		//so rgvarg[0] has the last argument and rgvarg[cArgs -1] has the first argument.
		//The method or property may change the values of elements within the array rgvarg,
		//but only if it has set the VT_BYREF flag. Otherwise, consider the elements as read-only.

		//For those implementing IDispatch::Invoke, Automation provides the DispGetParam function
		//to retrieve parameters from the argument vector and coerce them to the proper type.
		// Locate the parameter indicated by the given position, and
		// return it coerced to the given target VARTYPE (vtTarg).
		//WINOLEAUTAPI DispGetParam(DISPPARAMS * pdispparams, UINT position,
		//         VARTYPE vtTarg, VARIANT * pvarResult, UINT * puArgErr);
		//DispGetParam( &dispparams, , , ,  );

		DISPPARAMS * pDispParams = pInvokeParam->pDispParams;
		pDispParams->cArgs = nParamCount;

		// determine how to dispatch
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		switch (wInvokeFlag) {
	      case DISPATCH_PROPERTYPUT:
	      case DISPATCH_PROPERTYPUTREF:
			   pDispParams->cNamedArgs = 1;
			   pDispParams->rgdispidNamedArgs = &dispidNamed;
	         break;
	      case DISPATCH_PROPERTYGET:
	      case DISPATCH_METHOD:
	      case DISPATCH_PROPERTYGET|DISPATCH_METHOD:
	      default:
	         pDispParams->cNamedArgs = 0;
			 pDispParams->rgdispidNamedArgs = NULL;
	         break;
		}
		if ( nParamCount > 0 ) {
			pDispParams->rgvarg = new VARIANT[nParamCount];
			memset( pDispParams->rgvarg, 0, sizeof(VARIANT) * nParamCount );

			for ( int i = nParamCount - 1, j = 0; i >= 0; i--, j++ ) {
				jobject arg = env->GetObjectArrayElement( params, i );

				VARIANT* pArg = pDispParams->rgvarg + j;
				VariantInit( pArg );


				VARIANT *v = extractVariant(env, arg);
				// no escape from copy?
				VariantCopy( pArg, v );

				env->DeleteLocalRef(arg);
			}

		} else {
			pDispParams->rgvarg = NULL;
			pDispParams->cArgs = 0;
		}
	
		pInvokeParam->nParamCount = nParamCount;
		pInvokeParam->dispIdMember = dispMethodID;
		pInvokeParam->wFlags = (WORD)wInvokeFlag;

		if (pDispatchHWND) {
			// In-process server
			//Invoke for control (running in a different thread)
			//has to be call in control creation thread.
			//Control is displayed inside java awt component.
			// IS BLOCKING CALLING THREAD!!!
			HRESULT hr = StartInvoke(pInvokeParam);

			::WaitForSingleObject(g_heventDone, INFINITE);
			::ResetEvent(g_heventDone);
		} else {
			// Out-process server
			HRESULT hr = Invoke(pInvokeParam);
		}

    	// destroy InvokeParam here
		delete pInvokeParam;
			
	} catch (...) {
		cerr << "Unhandled exception: FAILED to Invoke." << endl;
		ThrowComException( env, DISP_E_EXCEPTION, "FAILED to Invoke." );
	}
}

// Invoke method on ActiveX control 
HRESULT WINAPIV StartInvoke(InvokeParam * pInvokeParam)
{
	HRESULT hr = 0;

	UINT msgId = WM_INVOKE;

	HWND hWnd = pInvokeParam->pDispatchHWND->hControlWnd;
//*	
	hr = PostMessage(hWnd, msgId, 0, (LPARAM) pInvokeParam);
	//cout << hr << "=PostMessage(hWnd=" << hWnd << "," << msgId << ",0,)" << endl;
//*/
/*	
	LRESULT res = SendMessage(hWnd, msgId, 0, (LPARAM) pInvokeParam);
	cout << res << "=SendMessage(hWnd=" << hWnd << "," << msgId << ",0,)" << endl;
	//SendMessageCallback();
//*/	
	return hr;
}

// Invokes method on ActiveX control
HRESULT Invoke(InvokeParam * pInvokeParam)
	//throw ThrowComException
{
	HRESULT hr = E_FAIL;
	JNIEnv * env = pInvokeParam->attachJNIEnv();
	if ( env->ExceptionOccurred() ) {
		pInvokeParam->detachJNIEnv(env);
		return hr;
	}
	
	try {
		IDispatch * pDispatch = pInvokeParam->pDispatchHWND->pDispatch;
		DISPPARAMS * pDispParams = pInvokeParam->pDispParams;
		VARIANT * pVarResult = pInvokeParam->pVarResult;
		EXCEPINFO * pExcepInfo = pInvokeParam->pExcepInfo;

/*
cout << " Invoke() on pDispatch=" << pDispatch 
<< " dispIdMember=" << pInvokeParam->dispIdMember
<< " wFlags=" << pInvokeParam->wFlags
<< " pDispParams=" << pDispParams
	<< " - cArgs=" << pDispParams->cArgs
<< " pVarResult=" << pVarResult
<< " pExcepInfo=" << pExcepInfo
<< " nArgErr=" << pInvokeParam->nArgErr
<< endl;
//*/
		hr = pDispatch->Invoke(
			pInvokeParam->dispIdMember,	// DISPID dispIdMember, // [in]
			pInvokeParam->riid,			// REFIID riid,   // [in]
			pInvokeParam->lcid,			// LCID lcid,   // [in]
			pInvokeParam->wFlags,		// WORD wFlags,      // [in]
			pDispParams,				// DISPPARAMS __RPC_FAR *pDispParams,  // [out][in]
			pVarResult,					// VARIANT __RPC_FAR *pVarResult,  // [out]
			pExcepInfo,					// EXCEPINFO __RPC_FAR *pExcepInfo,  // [out]
			&pInvokeParam->nArgErr		// UINT __RPC_FAR *puArgErr) = 0;   // [out]
		);
/*
cout << "Invoke(dispIdMember=" << pInvokeParam->dispIdMember << ") = " << hr
<< (SUCCEEDED(hr) ? " - SUCCEEDED" : " - FAILED") 
//<< ", pDispParams->rgvarg[0]=" << (pDispParams->cArgs > 0 ? UBSTR(pDispParams->rgvarg[0].bstrVal) : "")
<< endl;
//*/
		// cleanup any arguments that need cleanup
		int nParamCount = pInvokeParam->nParamCount;
		if (nParamCount > 0) {
			VARIANT* pArg;
			for ( int i = nParamCount - 1; i >= 0; i-- ) {
				pArg = pDispParams->rgvarg + i;
				switch ( pArg->vt ) {
	   				case VT_BSTR:
		   				::SysFreeString(pArg->bstrVal);
			   			break;
				}
			}
			delete[] pDispParams->rgvarg;
		}

		if ( FAILED( hr ) ) {
			cerr << "Invoke failed: " << hr << endl;
			if (pVarResult)
				::VariantClear(pVarResult);

			if ( hr == DISP_E_EXCEPTION ) {
				if ( pExcepInfo->pfnDeferredFillIn != NULL )
					pExcepInfo->pfnDeferredFillIn(pExcepInfo);

				ThrowComException( env, hr, pExcepInfo->bstrDescription,
					pExcepInfo->bstrSource, pExcepInfo->bstrHelpFile, pExcepInfo->dwHelpContext );
			} else {
				ThrowComException( env, hr, "Invoke failed." );
			}

		} else if ( SUCCEEDED( hr ) ) {
			static unsigned int MAX_TRIAL_COUNT = 100;
			static unsigned int invoke_count = 0;

			invoke_count++;
			if (MAX_TRIAL_COUNT > 0) {
				if (invoke_count > MAX_TRIAL_COUNT) {
   					LicenseChecker * pLC = Java2COMLicenseChecker::getInstance();
					if (pLC != NULL) {
						if ( pLC->isLicensed() ) {
							// do not check license anymore
							MAX_TRIAL_COUNT = 0;
   						} else {
							std::string * pError = pLC->find();
							ThrowComException( env, E_FAIL, pError->c_str() );
							// TODO: define licence fail code
							hr = E_FAIL;
						}
					}
				} else {
					//std::cout << "CheckLicense: #" << invoke_count << std::endl;
				}
			}

			if (pVarResult &&
				(V_VT(pVarResult) == VT_DISPATCH))// || V_VT(pVarResult) == VT_DISPATCH|VT_BYREF))
			{
				IDispatch * pDispatchResult = pVarResult->pdispVal;
				DispatchHWND * parent = pInvokeParam->pDispatchHWND;
				if (parent->hControlWnd) {
					// store child in temp map (to be invoked later in parent thread)
					DispatchHWND * pDispatchHWND = new DispatchHWND(
						pDispatchResult, parent->hCanvasWnd, parent->hControlWnd);
					IDispatchContainer::getInstance()->insert((jint) pDispatchResult, pDispatchHWND);
					//cout << "Created id=pCanvasDispatch: " << pCreateParam->id << "=" << pCanvasDispatch << std::endl;
				} else {
					//have to add ref (reference stored by java code)
					pDispatchResult->AddRef();
				}
			}
		}

		pInvokeParam->detachJNIEnv(env);
		return hr;

	} catch (...) {
		pInvokeParam->detachJNIEnv(env);
		return E_FAIL;
	}
}

/*
 * Class:     com_argus_activex_Dispatch
 * Method:    ReleaseObject
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_Dispatch_ReleaseObject
  (JNIEnv * env, jobject obj)
{
	if ( env->ExceptionOccurred() )
		return -1;

	try {
		jint pDispId = extractPDispatch(env, obj);
		if (!pDispId) {
			ThrowComException( env, DISP_E_EXCEPTION, "IDispatch_ReleaseObject(...), could not find IDispatch" );
			return 0;
		}

		DispatchHWND * pDispatchHWND = IDispatchContainer::getInstance()->find(pDispId);
		if (pDispatchHWND) {
			return IDispatchContainer::getInstance()->release(pDispId);
		}

		IDispatch * pDispatch = extractDispatch(env, obj);
		return pDispatch->Release();

	} catch (...) {
		//ThrowComException( env, DISP_E_EXCEPTION, "FAILED to Release Object." );
		cerr << "FAILED to Release Object." << endl;
		return 0;
	}
}

/*
 * Class:     com_argus_activex_Dispatch
 * Method:    InvokeCLSID
 * Signature: (ILjava/lang/String;[Lcom/argus/activex/JVariant;ISLcom/argus/activex/Variant;)V
 */
JNIEXPORT void JNICALL Java_com_argus_activex_Dispatch_InvokeCLSID
  (JNIEnv * env, jobject, jint, jstring, jobjectArray, jint, jshort, jobject)
{
   if ( env->ExceptionOccurred() )
      return;
      

}

/*
 * Class:     com_argus_activex_Dispatch
 * Method:    AddListener
 * Signature: (ILjava/lang/String;Ljava/util/EventListener;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_Dispatch_AddListener
  (JNIEnv * env, jobject, jint, jstring, jobject, jstring)
{
   if ( env->ExceptionOccurred() )
      return 0;
      
   jint id = 0;

   return id;
}


/*
 * Class:     com_argus_activex_Dispatch
 * Method:    RemoveListener
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_argus_activex_Dispatch_RemoveListener
  (JNIEnv * env, jobject, jint)
{
   if ( env->ExceptionOccurred() )
      return;
      

}
