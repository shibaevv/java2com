//---------------------------------------------------------------------------
#include "stdafx.h"
#include "Java2COMLicenseChecker.h"

//---------------------------------------------------------------------------
LicenseChecker * Java2COMLicenseChecker::pLC = NULL;
LicenseChecker * Java2COMLicenseChecker::createInstance(const char * pLicence) {
   pLC = new Java2COMLicenseChecker(pLicence == NULL ? "" : pLicence);
   return pLC;
}
LicenseChecker * Java2COMLicenseChecker::getInstance() {
   return pLC;
}

Java2COMLicenseChecker::Java2COMLicenseChecker(const char * pLicence)
   : LicenseChecker(pLicence)
{

/*******************************************************************************
trial message
*******************************************************************************/
   this->insert(
      "",
      "This is trial version of Java2COM. Limited to 100 method invocations." \
      "\nContact Argus Software (mail@argussoftware.net) for licensed version."
   );

//#define LarrySilvermintz
#ifdef LarrySilvermintz
///*******************************************************************************
//Digest.digest(
//"Date created: 2011-08-09\n" +
//"Receipt ID: FREE\n" +
//"Larry Silvermintz\n" +
//"Berkeley, CA, USA\n" +
//"phone: (510)705-1432\n" +
//"silvermintz@gmail.com\n" +
//"http://", Digest.MD5)
//License key: 810BBC06708A7760D0C4780FD0670700
//*******************************************************************************/
   this->insert(
      "810BBC06708A7760D0C4780FD0670700",
      "This is licensed version of Java2COM.\n" \
      "Licensed to Larry Silvermintz (510)705-1432 (Berkeley, CA, USA)."
   );
#endif

//#define HelpITSystems
#ifdef HelpITSystems
///*******************************************************************************
//Digest.digest(
//"Date created: 2007-01-15\n" +
//"Receipt ID: 5419-1512-4282-9187\n" +
//"HelpIT Systems Ltd.\n" +
//"Stephen Tootill\n" +
//"Stocks House, 9 North Street, LEATHERHEAD, Surrey, KT22 7AX, United Kingdom\n" +
//"phone: \n" +
//"grahamb@helpit.com\n" +
//"http://helpit.com", Digest.MD5)
//License key: BD6BDBD8D246A3BB1065085BEAF86496
//*******************************************************************************/
   this->insert(
      "BD6BDBD8D246A3BB1065085BEAF86496",
      "This is licensed version of Java2COM.\n" \
      "Licensed to HelpIT Systems Ltd. (United Kingdom)."
   );
#endif

//#define DanielLauzon
#ifdef DanielLauzon
///*******************************************************************************
//Digest.digest(
//"Date created: 2006-10-03" +
//" Pty. Ltd." +
//"Daniel Lauzon" +
//"18 Lavallee, Gatineau, Quebec, J8Z1P1, Canada" +
//"phone: " +
//"daniel.lauzon@sologlobe.com" +
//"http://www.", Digest.MD5)
//License key: 6291C0FA4DF92A106417381C27CAC862
//*******************************************************************************/
   this->insert(
      "6291C0FA4DF92A106417381C27CAC862",
      "This is licensed version of Java2COM.\n" \
      "Licensed to Daniel Lauzon (Canada)."
   );
#endif

//#define DuplessisLaurent
#ifdef DuplessisLaurent
///*******************************************************************************
//Digest.digest(
//"Date created: 2006-02-22" +
//" Pty. Ltd." +
//"Duplessis Laurent" +
//"353 chemin du haut des ponceaux, Rubelles, 77950, Seine et Marne, France" +
//"phone: 0662143878" +
//"lapecook@hotmail.com" +
//"http://www.", Digest.MD5)
//License key: 75B0D6A1C4C6AE91838DCE8954EEEA5B
//*******************************************************************************/
   this->insert(
      "75B0D6A1C4C6AE91838DCE8954EEEA5B",
      "This is licensed version of Java2COM.\n" \
      "Licensed to Duplessis Laurent (France)."
   );
#endif

//#define MatthewFord
#ifdef MatthewFord
///*******************************************************************************
//Digest.digest(
//"Forward Computing and Control Pty. Ltd." +
//"Dr. Matthew Ford" +
//"27 Cottee Cr. Terrigal, NSW 2260" +
//"mobile: 0419226364" +
//"matthew.ford@forward.com.au" +
//"http://www.forward.com.au", Digest.MD5)
//License key: 259D24559189596AB3AE977F4351996E
//*******************************************************************************/
   this->insert(
      "259D24559189596AB3AE977F4351996E",
      "This is licensed version of Java2COM.\n" \
      "Licensed to Forward Computing and Control Pty. Ltd."
   );
#endif

//#define UNSW
#ifdef UNSW
///*******************************************************************************
//Digest.digest(
//"Dr. Oleg Ostrovski, " +
//"The University of New South Wales, " +
//"School of Material Science and Engineering, " +
//"Sydney, NSW 2052, " +
//"Telephone: +61 (2) 9385 4439, " +
//"o.ostrovski@unsw.edu.au, " +
//"http://www.unsw.edu.au", Digest.MD5)
//License key: FF97614F933AB92C6776EA78B92D5A34
//*******************************************************************************/
   this->insert(
      "FF97614F933AB92C6776EA78B92D5A34",
      "This is licensed version of Java2COM.\n" \
      "Licensed to UNSW School of Material Science and Engineering."
   );
#endif

//#define PMI
#ifdef PMI
///*******************************************************************************
//Digest.digest(
//"PMI Mortgage Insurance" +
//"Mr. Michael HINTON" +
//"Sydney, NSW 2000" +
//"mobile: " +
//"email: " +
//"http://www.pmigroup.com.au", Digest.MD5)
//License key: B230FC34D6E7D9C37CE13405714331B7
//*******************************************************************************/
   this->insert(
      "B230FC34D6E7D9C37CE13405714331B7",
      "This is licensed version of Java2COM.\n" \
      "Licensed to PMI Mortgage Insurance,"
   );
#endif

//#define RobBarrett
#ifdef RobBarrett
///*******************************************************************************
//Digest.digest(
//"Coffee with Barretts, " +
//"Crystal & Rob Barrett, " +
//"40 Bek Road, Newton Hall, Durham, DH1 5LD, UK, " +
//"phone from US: 011 44 191 386 7739 " +
//"email: <rob@coffeewithbarretts.com> " +
//"http://coffeewithbarretts.com", Digest.MD5)
//License key: BAC09167C51D2A6547AA635B7040BA67
//*******************************************************************************/
   this->insert(
      "BAC09167C51D2A6547AA635B7040BA67",
      "This is licensed version of Java2COM.\n" \
      "Licensed to Rob Barrett, http://coffeewithbarretts.com"
   );
#endif

//#define WordReport
#ifdef WordReport
///*******************************************************************************
//Digest.digest(
//"WordReport trial" +
//"Mr. Valeri SHIBAEV" +
//"Sydney, NSW 2000" +
//"mobile: (61-2) 0412 586 556" +
//"email: shibaevv@argussoftware.net" +
//"http://argussoftware.net", Digest.MD5)
//License key: 2E7D504C2A73ADDE4E1B16F273D63051
//*******************************************************************************/
   this->insert(
      "2E7D504C2A73ADDE4E1B16F273D63051",
      "This is licensed limited version of Java2COM.\n" \
      "Licensed to <WordReport trial>."
   );
#endif

}

Java2COMLicenseChecker::~Java2COMLicenseChecker() {
   if (pLC == this)
      pLC = NULL;

   LicenseChecker::~LicenseChecker();
}

//string * Java2COMLicenseChecker::find( string key ) {
//   return LicenseChecker::find(key);
//}

