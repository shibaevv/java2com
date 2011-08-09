//---------------------------------------------------------------------------

#ifndef dispatchMapH
#define dispatchMapH
//---------------------------------------------------------------------------

//#include "dispatch.h"

#include <map>

using namespace std;

class DispatchHWND {
public:
	IDispatch * pDispatch;
	HWND hCanvasWnd;
	HWND hControlWnd;
public:
	DispatchHWND(IDispatch * pDispatch, HWND hCanvasWnd, HWND hControlWnd)
		: pDispatch(pDispatch), hCanvasWnd(hCanvasWnd), hControlWnd(hControlWnd)
	{
		pDispatch->AddRef();
	}
	~DispatchHWND()
	{
		if (pDispatch)
			pDispatch->Release();
	}
};

typedef map<jint, DispatchHWND*> IDispatchMap;
typedef map<jint, DispatchHWND*>::iterator IDispatchMapIterator;

class IDispatchContainer {
private:
   static IDispatchContainer * pDC;

private:
   IDispatchMap * pMap;

protected:
	IDispatchContainer();

public:
   //void insert( jint id, IDispatch*);
   //IDispatch* find( jint id );
   void insert( jint id, DispatchHWND * );
   DispatchHWND * find( jint id );
   jint release( jint id );

   static IDispatchContainer * getInstance();
	~IDispatchContainer();
};

#endif
