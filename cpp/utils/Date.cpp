// Date.cpp: implementation of the Date class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Date.h"

#include <stdio.h>

#include <sys/types.h>
#include <sys/timeb.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Date::Date()
{
	timeBuf = new char[255];
}

Date::~Date()
{
	delete timeBuf;
}

char * Date::ToString()
{
	// Get time string
	tm * tmptr = GetLocalTime();
	strcpy(timeBuf, asctime(tmptr));
	
	//struct timeb t;
	//char millisec[25];

	//ftime( &t );
	//memset( millisec, 0, sizeof( millisec ) );
	//sprintf( millisec, " Time:%ld.%d", t.time, t.millitm );
	//strcat( timeBuf, millisec );

	return timeBuf;

}

tm * Date::GetGMTime()
{
	time_t clock = time( (time_t*) NULL);
	return gmtime( &clock );
}

tm * Date::GetLocalTime()
{
	time_t clock = time( (time_t*) NULL);
	return localtime( &clock );
}

void Date::GetDateTimeStamp( char * pBuffer, const char * pPattern )
{
	memset( pBuffer, 0x00, strlen( pBuffer ) );

	timeb tb;
	ftime( &tb );

	tm * t = localtime( &tb.time );

	sprintf( pBuffer, "%d%d%d%d%d%d%d", 
		1900 + t->tm_year, t->tm_mon + 1, t->tm_mday, 
		t->tm_hour, t->tm_min, t->tm_sec, tb.millitm );

}
