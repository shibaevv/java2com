//---------------------------------------------------------------------------

#ifndef Java2COMLicenseCheckerH
#define Java2COMLicenseCheckerH

#include "stdafx.h"
//---------------------------------------------------------------------------
class Java2COMLicenseChecker : public LicenseChecker {
private:
   static LicenseChecker * pLC;

protected:
	Java2COMLicenseChecker(const char * pLicence);

public:
   static LicenseChecker * getInstance();
   static LicenseChecker * createInstance(const char * pLicence = "");

	virtual ~Java2COMLicenseChecker();
};

#endif
