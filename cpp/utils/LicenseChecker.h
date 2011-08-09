//---------------------------------------------------------------------------

#ifndef LicenseCheckerH
#define LicenseCheckerH
//---------------------------------------------------------------------------
#include <map>
#include <string>

using namespace std;

typedef map<string, string *> LicenseMap;
typedef map<string, string *>::iterator LicenseMapIterator;

class LicenseChecker {
private:
   string * pLicence;
   LicenseMap * pMap;

protected:
	LicenseChecker(const char * pLicence);

   void insert( string key, string * pDesc );
   void insert( string key, const char * pDesc );
   void remove( string key );
   
public:
   string * find( string key = "" );

   bool isLicensed();
   bool isRestricted();

   string * getLicensedInfo();

   virtual ~LicenseChecker();
};

#endif
