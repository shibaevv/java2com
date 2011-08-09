// ResourceManager.cpp: implementation of the ResourceManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResourceManager.h"
#include "XMLProcessor.h"
#include "ustring.h"

//////////////////////////////////////////////////////////////////////
// Static methods/members
//////////////////////////////////////////////////////////////////////

const char * ParameterData::APPLICATION_NAME		= "application-name";

const char * ParameterData::ERROR_EXIT_RESPONSE		= "error-exit-response"; // int

const char * ParameterData::BEEP					= "beep"; // boolean

const char * ParameterData::LOG						= "log"; // boolean
const char * ParameterData::LOG_STATUS_DIR			= "log-status-dir";
const char * ParameterData::LOG_WARNING_DIR			= "log-warning-dir";
const char * ParameterData::LOG_ERROR_DIR			= "log-error-dir";
const char * ParameterData::LOG_DEBUG_DIR			= "log-debug-dir";
const char * ParameterData::LOG_COMPUTER_NAME		= "log-computer-name";

const char * ParameterData::EVENT_MESSAGE_FILE		= "event-message-file";
const char * ParameterData::CATEGORY_MESSAGE_FILE	= "category-message-file";
const char * ParameterData::PARAMETER_MESSAGE_FILE	= "parameter-message-file";

const char * ParameterData::MESSAGE_TYPE_XPATH      = "message-type-xpath";

const char * ParameterData::ILLEGAL_CHARACTERS      = "illegal-characters";


ResourceManager * ResourceManager::resourceManager = new ResourceManager();

ResourceManager * ResourceManager::GetInstance()
{
	return resourceManager;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ResourceManager::ResourceManager()
{
	
}

ResourceManager::~ResourceManager()
{
	ClearParameters();
	ClearMessageExits();
}

void ResourceManager::ClearParameters() {

	for ( ConfigDataMapConstIterator i = params.begin(); i != params.end(); i++ )
		delete i->second;
	params.clear();

}

void ResourceManager::ClearMessageExits() {

	for ( ConfigDataMapConstIterator i = messageExits.begin(); i != messageExits.end(); i++ )
		delete i->second;
	messageExits.clear();

}

void ResourceManager::Init( const char * config, const char * schema ) throw()
{
	HRESULT hr;
	XMLProcessor xmlProcessor;
	IXMLDOMDocument2 * pDoc = xmlProcessor.Load( config, schema );

	IXMLDOMNodeList *pNodeList = 0;
	hr = pDoc->getElementsByTagName( UBSTR("parameter"), &pNodeList );
	if ( hr == S_OK )
		InitParameters( pNodeList );
	pNodeList->Release();

	hr = pDoc->getElementsByTagName( UBSTR("message-exit"), &pNodeList );
	if ( hr == S_OK )
		InitMessageExits( pNodeList );
	pNodeList->Release();
	
}

ParameterData * ResourceManager::GetParameterData( const char * name ) const
{
	//return "//Message[1]/Body[1]/@Type" );
    ConfigDataMapConstIterator i = params.find( string(name) );
    return i == params.end() ? 0 : reinterpret_cast< ParameterData * > ( i->second );
}

MessageExitData * ResourceManager::GetMessageExit( const char * name ) const
{
	//return "D:\\projects\\CMR\\MOM\\xml\\idw.xsd";
    ConfigDataMapConstIterator i = messageExits.find( string(name) );
    return i == messageExits.end() ? 0 : reinterpret_cast< MessageExitData * > ( i->second );
}

MessageExitData * ResourceManager::GetMessageExit( const BSTR name ) const
{
	size_t len = wcslen( name );
	char * name2 = new char[ len + 1 ];
	if ( ustrncpy( name2, name, len + 1 ) )
		return GetMessageExit( name2 );
	return 0;
}

void ResourceManager::InitParameters( IXMLDOMNodeList * pNodeList )
{
	ClearParameters();

	if ( !pNodeList )
		return;

	HRESULT hr;
	long listLength;
	hr = pNodeList->get_length( &listLength );

	if ( hr != S_OK || listLength == 0 )
		return;

	IXMLDOMNode *pNode;
	ParameterData * pParam;
	while ( pNodeList->nextNode( &pNode ) == S_OK ) {
		pParam = new ParameterData();
		pParam->Init( pNode );

		pNode->Release();

		params.insert( make_pair( pParam->GetName(), pParam ) );

	}

}

void ResourceManager::InitMessageExits( IXMLDOMNodeList * pNodeList )
{
	ClearMessageExits();

	if ( !pNodeList )
		return;

	HRESULT hr;
	long listLength;
	hr = pNodeList->get_length( &listLength );

	if ( hr != S_OK || listLength == 0 )
		return;

	IXMLDOMNode *pNode;
	MessageExitData * pParam;
	while ( pNodeList->nextNode( &pNode ) == S_OK ) {
		pParam = new MessageExitData();
		hr = pParam->Init( pNode );

		pNode->Release();

		messageExits.insert( make_pair( pParam->GetName(), pParam ) );

	}

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ConfigData::~ConfigData() 
{
	delete pName;
}

HRESULT ConfigData::GetNodeValue( IXMLDOMNode * pNode, BSTR name, VARIANT * value )
{
	HRESULT hr;
	IXMLDOMNamedNodeMap *pAttributeMap;

	hr = pNode->get_attributes( &pAttributeMap );
	if ( hr != S_OK ) {
		// TODO
		return hr;
	}

	IXMLDOMNode * pNode2;
	hr = pAttributeMap->getNamedItem( name, &pNode2 );
	if ( hr != S_OK ) {
		// TODO
		return hr;
	}

	VariantInit( value );
	hr = pNode2->get_nodeValue( value );
	pNode2->Release();

	return hr;

}


HRESULT ConfigData::Init( IXMLDOMNode * pNode )
{
	VARIANT value;

	// get <name/>
	HRESULT hr = GetNodeValue( pNode, UBSTR( "name" ), &value );
	if ( hr != S_OK ) {
		// TODO
		return hr;
	}

	delete pName;

	size_t len = wcslen( value.bstrVal );
	char * value2 = new char[ len + 1 ];
	hr = ustrncpy( value2, value.bstrVal, len + 1 );
	
	pName = new string( value2 );

	delete [] value2;
	VariantClear( &value );

	
	// get <enabled/>
	hr = GetNodeValue( pNode, UBSTR( "enabled" ), &value );
	if ( hr == S_OK ) {
		enabled = value.boolVal == VARIANT_FALSE ? false : true;
	} else {
		enabled = true;
		hr = S_OK;
	}

	
	return hr;

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ParameterData::~ParameterData() 
{
	delete pValue;

	ConfigData::~ConfigData();
}

HRESULT ParameterData::Init( IXMLDOMNode * pNode )
{
	HRESULT hr;
	hr = ConfigData::Init( pNode );


	VARIANT value;
	hr = GetNodeValue( pNode, UBSTR( "value" ), &value );
	if ( hr != S_OK ) {
		// TODO
		return hr;
	}

	delete pValue;

	size_t len = wcslen( value.bstrVal );
	char * value2 = new char[ len + 1 ];
	hr = ustrncpy( value2, value.bstrVal, len + 1 );
	
	pValue = new string( value2 );

	delete [] value2;
	VariantClear( &value );

	return hr;

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MessageExitData::~MessageExitData() 
{
	delete pSchema;

	ConfigData::~ConfigData();
}

HRESULT MessageExitData::Init( IXMLDOMNode * pNode )
{
	ConfigData::Init( pNode );


	VARIANT value;
	HRESULT hr = GetNodeValue( pNode, UBSTR( "schema" ), &value );
	if ( hr != S_OK ) {
		// TODO
		return hr;
	}

	delete pSchema;

	size_t len = wcslen( value.bstrVal );
	char * value2 = new char[ len + 1 ];
	hr = ustrncpy( value2, value.bstrVal, len + 1 );
	
	pSchema = new string( value2 );

	delete [] value2;
	VariantClear( &value );

	return hr;

}
