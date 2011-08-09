//---------------------------------------------------------------------------
#include "stdafx.h"
#include "dispatchMap.h"

IDispatchContainer * IDispatchContainer::pDC = new IDispatchContainer();
IDispatchContainer * IDispatchContainer::getInstance() {
   return pDC;
}

IDispatchContainer::IDispatchContainer() {
   pMap = new IDispatchMap();
}
IDispatchContainer::~IDispatchContainer() {
	if ( pDC == this )
		pDC = NULL;

	if (!pMap)
		return;

	for ( IDispatchMapIterator p = pMap->begin(); p != pMap->end(); p++ ) {
		DispatchHWND * pDispatchHWND = p->second;
		pDispatchHWND->pDispatch->Release();
	}
	pMap->clear();
	delete pMap;
	pMap = NULL;
}

void IDispatchContainer::insert( jint id, DispatchHWND * pDispatchHWND ) {
   if (pMap)
      pMap->insert( make_pair( id, pDispatchHWND ) );
}

DispatchHWND * IDispatchContainer::find( jint id ) {
   IDispatchMapIterator p = pMap->find( id );
   return p == pMap->end() ? NULL : p->second;
}

jint IDispatchContainer::release( jint id ) {
	DispatchHWND * pDispatchHWND = find( id );
	if (pDispatchHWND) {
		pMap->erase( id );
		delete pDispatchHWND;
	}
	return 0;
}
