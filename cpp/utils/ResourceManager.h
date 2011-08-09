////////////////////////////////////////////////////////////////////////////////
// Company:    AQIS                                                           //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    To load recources into memory								  //
//             Singleton pattern                                              //
//			   private ctor/dtor prevent this class							  //
//			   from instantiating by new operator							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
// ResourceManager.h: interface for the ResourceManager class.
// 
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_RESOURCEMANAGER_H__4F72D5F3_FE00_4AE8_83A7_204676F84F84__INCLUDED_)
#define AFX_RESOURCEMANAGER_H__4F72D5F3_FE00_4AE8_83A7_204676F84F84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wtypes.h>
#include "ubstr.h"

#import "msxml4.dll" raw_interfaces_only
//using namespace MSXML2; // #define __USE_MSXML2_NAMESPACE__


// You might need to add the msxml4/sdk/(inc, lib) directories 
// to the Tools->Options...->Directories in Visual Studio.
//
// You might also need to append "msxml2.lib" to the
// Project->Settings...->Link->Object/Libray Modules field.

#include <msxml2.h>

#include <map>
#include <string>
using namespace std;


class ConfigData;
typedef map<string, ConfigData *> ConfigDataMap;
typedef ConfigDataMap::iterator ConfigDataMapIterator;
typedef ConfigDataMap::const_iterator ConfigDataMapConstIterator;


class ConfigData
{
private:
	string * pName;
	bool enabled;

protected:
	HRESULT GetNodeValue( IXMLDOMNode * pNode, BSTR name, VARIANT * value );

public:
	ConfigData() : pName(0) {}
	virtual ~ConfigData();

	virtual HRESULT Init( IXMLDOMNode * pNode );

	const char * GetName() const { return pName->c_str(); }
	bool IsEnabled() { return enabled; }

};


class ParameterData : public ConfigData
{
private:
	string * pValue;

public:
	static const char * APPLICATION_NAME;

	static const char * ERROR_EXIT_RESPONSE;	

	static const char * BEEP;

	static const char * LOG;
	static const char * LOG_STATUS_DIR;
	static const char * LOG_WARNING_DIR;
	static const char * LOG_ERROR_DIR;
	static const char * LOG_DEBUG_DIR;
	static const char * LOG_COMPUTER_NAME;

	static const char * EVENT_MESSAGE_FILE;
	static const char * CATEGORY_MESSAGE_FILE;
	static const char * PARAMETER_MESSAGE_FILE;


	static const char * MESSAGE_TYPE_XPATH;

	static const char * ILLEGAL_CHARACTERS;

	ParameterData() : ConfigData(), pValue(0)  {}
	virtual ~ParameterData();

	virtual HRESULT Init( IXMLDOMNode * pNode );

	const char * GetValue() const { return pValue->c_str(); }

};


class MessageExitData : public ConfigData
{
private:
	string * pSchema;

public:
	MessageExitData() : ConfigData(), pSchema(0)  {}
	virtual ~MessageExitData();

	virtual HRESULT Init( IXMLDOMNode * pNode );

	const char * GetSchema() const { return pSchema->c_str(); }

};


class ResourceManager  
{
private:
	static ResourceManager * resourceManager;

	ConfigDataMap params;
	ConfigDataMap messageExits;

	ResourceManager();
	~ResourceManager();

	void ClearParameters();
	void InitParameters( IXMLDOMNodeList * pNodeList );

	void ClearMessageExits();
	void InitMessageExits( IXMLDOMNodeList * pNodeList );

public:
	static ResourceManager * GetInstance();

	void Init( const char * config, const char * schema = 0 ) throw(); //XMLException

	ParameterData * GetParameterData( const char * name ) const;

	MessageExitData * GetMessageExit( const char * name ) const;
	MessageExitData * GetMessageExit( const BSTR name ) const;

};

#endif // !defined(AFX_RESOURCEMANAGER_H__4F72D5F3_FE00_4AE8_83A7_204676F84F84__INCLUDED_)
