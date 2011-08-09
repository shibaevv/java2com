// EventLog.cpp: implementation of the EventLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EventLog.h"

#include "Exception.h"


//////////////////////////////////////////////////////////////////////
// static members/methods
//////////////////////////////////////////////////////////////////////

EventLog * EventLog::pEventLog = 0;

const char * EventLog::APPLICATION = "Application";

EventLog * EventLog::GetInstance( const char * pEventSource, const char * pMachineName )
{
	bool init = !pEventLog || pEventSource;

	if ( !pEventLog )
		pEventLog = new EventLog();

	if ( init )
		pEventLog->Init( pEventSource, pMachineName );

	return pEventLog;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EventLog::EventLog()
{
	hEventSource = 0;
	pEventSource = 0;
	pMachineName = 0;
}

EventLog::~EventLog()
{
	UnInit();
}


void EventLog::Init( const char * pEventSource, const char * pMachineName )
{
	UnInit();

	this->pEventSource = new std::string( pEventSource );//strdup( pEventSource );
	
	if ( !pMachineName ) {
	    this->pMachineName = new char[ MAX_COMPUTERNAME_LENGTH + 1 ];
		DWORD nSize = MAX_COMPUTERNAME_LENGTH;
		GetComputerName( this->pMachineName, &nSize );
	} else {
		this->pMachineName = strdup( pMachineName );
	}

    wCategory = 0;
	lpUserSid = 0;

	hEventSource = RegisterEventSource( this->pMachineName, this->pEventSource->c_str() );

}
void EventLog::UnInit()
{
    if ( hEventSource )
		DeregisterEventSource( hEventSource );
	hEventSource = 0;

	delete pEventSource;
	pEventSource = 0;

	delete [] pMachineName;
	pMachineName = 0;
}

// Add an event source in the registry 
// (i.e., associate an event source with a specific event log).
long EventLog::AddEventSourceToRegistry (
	const char * pLogName,			// Name of the event log
	const char * pMsgFile,			// Name of the event message file
	const char * pCatagoryFile,		// Name of the event category file
	const char * pParamFile,		// Name of the event parameter file
	DWORD   dwCount,				// Number of event categories supported
	DWORD   dwTypes)				// Event types supported
{

	// Construct the event source key name
	char logKey[120];
	strcpy( logKey, "SYSTEM\\CurrentControlSet\\Services\\EventLog\\" );
	strcat( logKey, pLogName );
	strcat( logKey, "\\" );
	strcat( logKey, pEventSource->c_str() );

	// Open the event source key
	DWORD dwResult;
	HKEY  hLogKey = NULL;
	long lError = RegCreateKeyEx( HKEY_LOCAL_MACHINE, logKey, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hLogKey, &dwResult );

	if ( lError != ERROR_SUCCESS )
		return lError;

	// Write the name/value pairs
	if ( pMsgFile ) {
		RegSetValueEx( hLogKey, "EventMessageFile", 0, REG_SZ, 
			(const BYTE *)pMsgFile, lstrlen( pMsgFile ) + 1 );
	}

	RegSetValueEx( hLogKey, "TypesSupported", 0, REG_DWORD, 
		(LPBYTE) &dwTypes, sizeof(DWORD) );

	RegSetValueEx( hLogKey, "CategoryCount", 0, REG_DWORD, 
		(LPBYTE) &dwCount, sizeof(DWORD) );

	if ( pCatagoryFile ) {
		RegSetValueEx( hLogKey, "CategoryMessageFile", 0, REG_SZ,
			(const BYTE *)pCatagoryFile, lstrlen( pCatagoryFile ) + 1 );
	}

	if ( pParamFile ) {
		RegSetValueEx( hLogKey, "ParameterMessageFile", 0, REG_SZ, 
			(const BYTE *)pParamFile, lstrlen( pParamFile ) + 1 );
	}

	RegCloseKey( hLogKey );

	return lError;
}

// Removing an event source is almost as simple as deleting the event
// source's key. The event log key's Source value must also be updated 
// by removing the name of the event source. This operation should be 
// performed automatically for you by the event logging service when 
// the event source key is deleted but it isn't. So you must perform
// the removal manually.
long EventLog::RemoveEventSourceFromRegistry ( const char * pLogName )
{
	// Construct the event log key name
	char logKey[120];
	lstrcpy( logKey, "SYSTEM\\CurrentControlSet\\Services\\EventLog\\" );
	lstrcat( logKey, pLogName );

	// Open the event log key
	HKEY  hLogKey = NULL;
	long lError = RegOpenKey( HKEY_LOCAL_MACHINE, logKey, &hLogKey );

	if ( lError != ERROR_SUCCESS )
		return lError;

	// Remove the event source key
	RegDeleteKey( hLogKey, pEventSource->c_str() ); 
	RegCloseKey( hLogKey );
	
	return lError;
}


bool EventLog::Write(
	const char ** ppMsgs,
	const WORD    wNumStrings,
	const DWORD   dwEventID,
	const WORD    wEventType)
{
    if ( !hEventSource ) {
		char buffer[33];
		ltoa( GetLastError(), buffer, 10 );
		
		std::string msg( "EventLog::Write() RegisterEventSource: " );
		msg.append( buffer );

		throw Exception( msg.c_str() );

    }

	bool res = 
		ReportEvent( 
			hEventSource,				// Handle of event source
			wEventType,					// Event type
			wCategory,					// Event category
			dwEventID,					// Event identifier
			lpUserSid,					// User Security IDentifer
			wNumStrings,				// Number of strings to merge with message
			0,							// Size of binary data (in bytes)
			ppMsgs,					    // Array of strings to merge with message
			NULL ) == TRUE;				// Address of binary data

    if ( !res ) {
		char buffer[33];
		ltoa( GetLastError(), buffer, 10 );
		
		std::string msg( "EventLog::Write() ReportEvent: " );
		msg.append( buffer );

		throw Exception( msg.c_str() );

    }

	return res;

}

bool EventLog::Write(
	const char *  pMsg, 
	const DWORD   dwEventID,
	const WORD    wEventType)
{
	const WORD wNumStrings = 1;
	const char * pMsgs[ wNumStrings ];
	pMsgs[0] = pMsg;

	return 
		Write(
			pMsgs,
			wNumStrings,
			dwEventID,
			wEventType
		);

}

DWORD WINAPI EventLog::ThreadFuncWrite( LPVOID lpParam ) 
{ 
	const std::string ** parameters = (const std::string **) lpParam;

	const char *  pEventSource = parameters[0]->c_str();

	const char *  pMsg =       parameters[1]->c_str();
	DWORD   dwEventID  = atol( parameters[2]->c_str() );
	WORD    wEventType = atoi( parameters[3]->c_str() );

	const char *  pMachineName = parameters[4] ? parameters[4]->c_str() : 0;

	DWORD res = EventLog::GetInstance()->Write( pMsg, dwEventID, wEventType );

	// do cleanup
	for ( int i = 0; i < 5; i++ )
		delete parameters[i];
	delete parameters;

    return res;

} 

void EventLog::WriteA(
	const char *  pMsg, 
	const DWORD   dwEventID,
	const WORD    wEventType)
{
	const std::string ** parameters = new const std::string*[5];

	parameters[0] = new std::string( *pEventSource );

	parameters[1] = new std::string( pMsg );

    char pEventID[32];
    ltoa( dwEventID, pEventID, 10 );
	parameters[2] = new std::string( pEventID );

    char pEventType[20];
    itoa( wEventType, pEventType, 10 );
	parameters[3] = new std::string( pEventType );

	parameters[4] = new std::string( pMachineName );

	// Get ProcAddress for Thread-Func and create/run the thread.
	DWORD pThreadId;
	HANDLE hThread = CreateThread(
		NULL,			// LPSECURITY_ATTRIBUTES lpThreadAttributes
		0,				// DWORD dwStackSize
		(LPTHREAD_START_ROUTINE) (&EventLog::ThreadFuncWrite), // LPTHREAD_START_ROUTINE lpStartAddress
		(LPVOID) parameters,	// LPVOID lpParameter
		0,				// DWORD dwCreationFlags
		&pThreadId		// LPDWORD lpThreadId
	);

	// Return to caller app.

};

// Determine if the application is executing under Windows NT (or not).
bool EventLog::IsNT()
{
  OSVERSIONINFO vi;
  vi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );

  GetVersionEx( &vi );

  return ( vi.dwPlatformId == VER_PLATFORM_WIN32_NT ? true : false );

}
