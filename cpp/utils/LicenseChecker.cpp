//---------------------------------------------------------------------------
#include "stdafx.h"
#include "LicenseChecker.h"

//---------------------------------------------------------------------------
LicenseChecker::LicenseChecker(const char * pLicence) {
   this->pLicence = new string(pLicence == NULL ? "" : pLicence);
   pMap = new LicenseMap();
}
LicenseChecker::~LicenseChecker() {
   if (pMap == NULL)
      return;

   for ( LicenseMapIterator p = pMap->begin(); p != pMap->end(); p++ )
      delete p->second;
   pMap->clear();
   delete pMap;
   pMap = NULL;

   delete pLicence;
   pLicence = NULL;
}

void LicenseChecker::insert( string key, string * pDesc ) {
   if (pMap)
      pMap->insert( make_pair( key, pDesc ) );
}
void LicenseChecker::insert( string key, const char * pDesc ) {
   insert(key, new string(pDesc));
}
void LicenseChecker::remove( string key ) {
   string * pDesc = find( key );
   if ( pDesc == NULL )
      return;

   delete pDesc;
   if (pMap)
      pMap->erase( key );
}

string * LicenseChecker::find( string key ) {
   if (!pMap)
      return NULL;
   
   LicenseMapIterator p = pMap->find( key );
   return p == pMap->end() ? NULL : p->second;
}

bool LicenseChecker::isLicensed() {

   string * pDesc = getLicensedInfo();
   return pDesc != NULL && !pDesc->empty();

}

bool LicenseChecker::isRestricted() {

   string * pDesc = getLicensedInfo();
   return pDesc != NULL && !pDesc->empty();

}

string * LicenseChecker::getLicensedInfo() {

   if (!pMap || pLicence->empty())
      return NULL;

   return find( *pLicence );

}


