// EventLog.h: interface for the EventLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTLOG_H__2FF97E12_6AB1_481A_A800_CA54CA0B2133__INCLUDED_)
#define AFX_EVENTLOG_H__2FF97E12_6AB1_481A_A800_CA54CA0B2133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

//
// The types of events that can be logged <winnt.h>.
//
//#define EVENTLOG_SUCCESS                0X0000
//#define EVENTLOG_ERROR_TYPE             0x0001
//#define EVENTLOG_WARNING_TYPE           0x0002
//#define EVENTLOG_INFORMATION_TYPE       0x0004
//#define EVENTLOG_AUDIT_SUCCESS          0x0008
//#define EVENTLOG_AUDIT_FAILURE          0x0010


class EventLog  
{
private:
	static EventLog * pEventLog;

	std::string * pEventSource;
    char *  pMachineName;

    WORD    wCategory;

	PSID    lpUserSid;

	HANDLE  hEventSource;

	static DWORD WINAPI ThreadFuncWrite( LPVOID lpParam );

	void Init( const char * pEventSource, const char * pMachineName = 0 );
	void UnInit();

public:
	static const char * APPLICATION;

	static EventLog * GetInstance( const char * pEventSource = 0, const char * pMachineName = 0 );

	static bool IsNT();

	EventLog();
	~EventLog();

	long AddEventSourceToRegistry (
		const char * lpLogName,			// Name of the event log
		const char * lpMsgFile,			// Name of the event message file
		const char * lpCatagoryFile,	// Name of the event category file
		const char * lpParamFile,		// Name of the event parameter file
		DWORD   dwCount,				// Number of event categories supported
		DWORD   dwTypes);				// Event types supported

	long RemoveEventSourceFromRegistry ( 
		const char * pLogName );		// Name of the event log


	bool Write( 
		const char *  pMsg,
		const DWORD   dwEventID,
		const WORD    wEventType = EVENTLOG_INFORMATION_TYPE 
	);

	bool Write(
		const char ** ppMsgs,
		const WORD    wNumStrings,
		const DWORD   dwEventID,
		const WORD    wEventType = EVENTLOG_INFORMATION_TYPE
	);


	void WriteA(
		const char *  pMsg, 
		const DWORD   dwEventID,
		const WORD    wEventType = EVENTLOG_INFORMATION_TYPE
	);

};

#endif // !defined(AFX_EVENTLOG_H__2FF97E12_6AB1_481A_A800_CA54CA0B2133__INCLUDED_)
