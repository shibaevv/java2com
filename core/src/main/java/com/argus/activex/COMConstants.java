/*
 *              Argus Software Pty Ltd License Notice
 * 
 * The contents of this file are subject to the Argus Software Pty Ltd
 * License Version 1.0 (the "License"). You may not use this file except
 * in compliance with the License. A copy of the License is available at
 * http://www.argussoftware.net/license/license_agreement.html
 * 
 * The Original Code is argus. The Initial Developer of the Original
 * Code is Argus Software Pty Ltd, All Rights Reserved.
 */

package com.argus.activex;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Argus Software Pty Ltd</p>
 * @author Valeri SHIBAEV
 * @author Last Updated By:   $Author: Valera $
 * @version                   $Revision: 1.3 $
 */

public interface COMConstants {

    // wtypes.h
    public static final short VT_EMPTY = 0;
    public static final short VT_NULL = 1;
    public static final short VT_I2 = 2;
    public static final short VT_I4 = 3;
    public static final short VT_R4 = 4;
    public static final short VT_R8 = 5;
    public static final short VT_CY = 6;
    public static final short VT_DATE = 7;
    public static final short VT_BSTR = 8;
    public static final short VT_DISPATCH = 9;
    public static final short VT_ERROR = 10;
    public static final short VT_BOOL = 11;
    public static final short VT_VARIANT = 12;
    public static final short VT_UNKNOWN = 13;
    public static final short VT_DECIMAL = 14;
    public static final short VT_I1 = 16;
    public static final short VT_UI1 = 17;
    public static final short VT_UI2 = 18;
    public static final short VT_UI4 = 19;
    public static final short VT_I8 = 20;
    public static final short VT_UI8 = 21;
    public static final short VT_INT = 22;
    public static final short VT_UINT = 23;
    public static final short VT_VOID = 24;
    public static final short VT_HRESULT = 25;
    public static final short VT_PTR = 26;
    public static final short VT_SAFEARRAY = 27;
    public static final short VT_CARRAY = 28;
    public static final short VT_USERDEFINED = 29;
    public static final short VT_LPSTR = 30;
    public static final short VT_LPWSTR = 31;
    public static final short VT_FILETIME = 64;
    public static final short VT_BLOB = 65;
    public static final short VT_STREAM = 66;
    public static final short VT_STORAGE = 67;
    public static final short VT_STREAMED_OBJECT = 68;
    public static final short VT_STORED_OBJECT = 69;
    public static final short VT_BLOB_OBJECT = 70;
    public static final short VT_CF = 71;
    public static final short VT_CLSID = 72;
    public static final short VT_VECTOR = 4096;
    public static final short VT_ARRAY = 8192;
    public static final short VT_BYREF = 16384; // 0x4000
    
    //typedef enum tagINVOKEKIND {
    public static final short DISPATCH_METHOD = 1;
    public static final short DISPATCH_PROPERTYGET = 2;
    public static final short DISPATCH_PROPERTYPUT = 4;
    public static final short DISPATCH_PROPERTYPUTREF = 8;
    //} INVOKEKIND;

    //typedef enum tagVARKIND {
    public static final short VAR_PERINSTANCE   = 0;
    public static final short VAR_STATIC        = 1;
    public static final short VAR_CONST         = 2;
    public static final short VAR_DISPATCH      = 3;
    //} VARKIND;
    
    //enum tagTYPEKIND oaidl.h
    public static final short TKIND_ENUM        = 0;
    public static final short TKIND_RECORD      = 1;
    public static final short TKIND_MODULE      = 2;
    public static final short TKIND_INTERFACE   = 3;
    public static final short TKIND_DISPATCH    = 4;
    public static final short TKIND_COCLASS     = 5;
    public static final short TKIND_ALIAS       = 6;
    public static final short TKIND_UNION       = 7;
    public static final short TKIND_MAX         = 8;

    //enum tagCALLCONV  oaidl.h
    public static final short CC_FASTCALL       = 0;
    public static final short CC_CDECL          = 1;
    public static final short CC_MSCPASCAL      = CC_CDECL + 1;
    public static final short CC_PASCAL         = CC_MSCPASCAL;
    public static final short CC_MACPASCAL      = CC_PASCAL + 1;
    public static final short CC_STDCALL        = CC_MACPASCAL + 1;
    public static final short CC_FPFASTCALL     = CC_STDCALL + 1;
    public static final short CC_SYSCALL        = CC_FPFASTCALL + 1;
    public static final short CC_MPWCDECL       = CC_SYSCALL + 1;
    public static final short CC_MPWPASCAL      = CC_MPWCDECL + 1;
    public static final short CC_MAX            = CC_MPWPASCAL + 1;
    
    //enum tagFUNCKIND
    public static final short FUNC_VIRTUAL      = 0;
    public static final short FUNC_PUREVIRTUAL  = 1;
    public static final short FUNC_NONVIRTUAL   = 2;
    public static final short FUNC_STATIC       = 3;
    public static final short FUNC_DISPATCH     = 4;
    
    //enum tagCLSCTX {
    public static final int CLSCTX_INPROC_SERVER        = 0x1;
    public static final int CLSCTX_INPROC_HANDLER       = 0x2;
    public static final int CLSCTX_LOCAL_SERVER         = 0x4;
    public static final int CLSCTX_INPROC_SERVER16      = 0x8;
    public static final int CLSCTX_REMOTE_SERVER        = 0x10;
    public static final int CLSCTX_INPROC_HANDLER16     = 0x20;
    public static final int CLSCTX_INPROC_SERVERX86     = 0x40;
    public static final int CLSCTX_INPROC_HANDLERX86    = 0x80;
    public static final int CLSCTX_ESERVER_HANDLER      = 0x100;
    public static final int CLSCTX_RESERVED             = 0x200;
    public static final int CLSCTX_NO_CODE_DOWNLOAD     = 0x400;
    public static final int CLSCTX_NO_WX86_TRANSLATION  = 0x800;
    public static final int CLSCTX_NO_CUSTOM_MARSHAL    = 0x1000;
    public static final int CLSCTX_ENABLE_CODE_DOWNLOAD = 0x2000;
    public static final int CLSCTX_NO_FAILURE_LOG       = 0x4000;
    // }    CLSCTX;
    public static final int CLSCTX_SERVER = 
        CLSCTX_INPROC_SERVER |
        CLSCTX_LOCAL_SERVER |
        CLSCTX_REMOTE_SERVER;
    public static final int CLSCTX_ALL = 
        CLSCTX_INPROC_SERVER | 
        CLSCTX_INPROC_HANDLER |
        CLSCTX_LOCAL_SERVER | 
        CLSCTX_REMOTE_SERVER;
    
/*
typedef enum tagFUNCFLAGS {
   FUNCFLAG_FRESTRICTED =   1
      , FUNCFLAG_FSOURCE =   0x2
      , FUNCFLAG_FBINDABLE =   0x4
      , FUNCFLAG_FREQUESTEDIT =   0x8
      , FUNCFLAG_FDISPLAYBIND =   0x10
      , FUNCFLAG_FDEFAULTBIND =   0x20
      , FUNCFLAG_FHIDDEN =   0x40
        , FUNCFLAG_FUSESGETLASTERROR =         0x80
        , FUNCFLAG_FDEFAULTCOLLELEM=      0x100
        , FUNCFLAG_FUIDEFAULT =            0x200
        , FUNCFLAG_FNONBROWSABLE =         0x400
        , FUNCFLAG_FREPLACEABLE =         0x800
      , FUNCFLAG_FIMMEDIATEBIND   =      0x1000
#ifdef _MAC
    , FUNCFLAG_FORCELONG  = 2147483647
#endif
} FUNCFLAGS;

Value 	Description
FUNCFLAG_FRESTRICTED 	The function should not be accessible from macro languages. This flag is intended for system-level functions or functions that type browsers should not display.
FUNCFLAG_FSOURCE 	The function returns an object that is a source of events.
FUNCFLAG_FBINDABLE 	The function that supports data binding.
FUNCFLAG_FREQUESTEDIT 	When set, any call to a method that sets the property results first in a call to IPropertyNotifySink::OnRequestEdit. The implementation of OnRequestEdit determines if the call is allowed to set the property.
FUNCFLAG_FDISPLAYBIND 	The function that is displayed to the user as bindable. FUNC_FBINDABLE must also be set.
FUNCFLAG_FDEFAULTBIND 	The function that best represents the object. Only one function in a type information can have this attribute.
FUNCFLAG_FHIDDEN 	The function should not be displayed to the user, although it exists and is bindable.
FUNCFLAG_USESGETLASTERROR 	The function supports GetLastError. If an error occurs during the function, the caller can call GetLastError to retrieve the error code.
FUNCFLAG_FDEFAULTCOLLELEM 	Permits an optimization in which the compiler looks for a member named ÂxyzÂ on the type of ÂabcÂ. If such a member is found and is flagged as an accessor function for an element of the default collection, then a call is generated to that member function. Permitted on members in dispinterfaces and interfaces; not permitted on modules. For more information, refer to defaultcollelem in Type Libraries and the Object Description Language.
FUNCFLAG_FUIDEFAULT 	The type information member is the default member for display in the user interface.
FUNCFLAG_FNONBROWSABLE 	The property appears in an object browser, but not in a properties browser.
FUNCFLAG_FREPLACEABLE 	Tags the interface as having default behaviors.
FUNCFLAG_FIMMEDIATEBIND 	Mapped as individual bindable properties.

Note   FUNCFLAG_FHIDDEN means that the property should never be shown in object browsers, property browsers, and so on. This function is useful for removing items from an object model. Code can bind to the member, but the user will never know that the member exists.

FUNCFLAG_FNONBROWSABLE means that the property should not be displayed in a properties browser. It is used in circumstances in which an error would occur if the property were shown in a properties browser.

FUNCFLAG_FRESRICTED means that macro-oriented programmers should not be allowed to access this member. These members are usually treated as _FHIDDEN by tools such as Visual Basic, with the main difference being that code cannot bind to those members.
Examples

    * The IsSelected property for a control. Setting it to False would confuse a user if the properties browser was focus-oriented.
    * Properties that take a long time to evaluate (for example, a Count property for a database object). The time to evaluate might take longer than a user is willing to wait.
    * Properties that have side effects.


#define IMPLTYPEFLAG_FDEFAULT   0x1
#define IMPLTYPEFLAG_FSOURCE      0x2
#define IMPLTYPEFLAG_FRESTRICTED   0x4
#define IMPLTYPEFLAG_FDEFAULTVTABLE   0x8

Value 	Description
IMPLTYPEFLAG_FDEFAULT 	The interface or dispinterface represents the default for the source or sink.
IMPLTYPEFLAG_FSOURCE 	This member of a coclass is called rather than implemented.
IMPLTYPEFLAG_FRESTRICTED 	The member should not be displayed or programmable by users.
IMPLTYPEFLAG_FDEFAULTVTABLE 	Sinks receive events through the VTBL.

typedef enum tagFUNCKIND {
   FUNC_VIRTUAL,
   FUNC_PUREVIRTUAL,
   FUNC_NONVIRTUAL,
   FUNC_STATIC,
   FUNC_DISPATCH,
} FUNCKIND;
 

Value 	Description
FUNC_PUREVIRTUAL 	The function is accessed through the virtual function table (VTBL), and takes an implicit this pointer.
FUNC_VIRTUAL 	The function is accessed the same as PUREVIRTUAL, except the function has an implementation.
FUNC_NONVIRTUAL 	The function is accessed by static address and takes an implicit this pointer.
FUNC_STATIC 	The function is accessed by static address and does not take an implicit this pointer.
FUNC_DISPATCH 	The function can be accessed only through IDispatch. 

typedef enum tagINVOKEKIND {
   INVOKE_FUNC = DISPATCH_METHOD,
   INVOKE_PROPERTYGET = DISPATCH_PROPERTYGET,
   INVOKE_PROPERTYPUT = DISPATCH_PROPERTYPUT,
   INVOKE_PROPERTYPUTREF = DISPATCH_PROPERTYPUTREF
#ifdef _MAC
   , INVOKE_FORCELONG = 2147483647
#endif
} INVOKEKIND;
 

Value 	Description
INVOKE_FUNC 	The member is called using a normal function invocation syntax.
INVOKE_PROPERTYGET 	The function is invoked using a normal property-access syntax.
INVOKE_PROPERTYPUT 	The function is invoked using a property value assignment syntax. Syntactically, a typical programming language might represent changing a property in the same way as assignment. For example:
object.property : = value.
INVOKE_PROPERTYPUTREF 	The function is invoked using a property reference assignment syntax.

In C, value assignment is written as *pobj1 = *pobj2, while reference assignment is written as pobj1 = pobj2. Other languages have other syntactic conventions. A property or data member can support only a value assignment, a reference assignment, or both. For a detailed description of property functions see Dispatch Interface and API Functions. The INVOKEKIND enumeration constants are the same constants that are passed to IDispatch::Invoke to specify the way in which a function is invoked.

#define PARAMFLAG_NONE         0
#define PARAMFLAG_FIN            0x1
#define PARAMFLAG_FOUT         0x2
#define PARAMFLAG_FLCID         0x4
#define PARAMFLAG_FRETVAL      0x8
#define PARAMFLAG_FOPT         0x10
#define PARAMFLAG_FHASDEFAULT   0x20
#define PARAMFLAG_FHASCUSTDATA   0x40
 

Value 	Description
PARAMFLAG_NONE 	Whether the parameter passes or receives information is unspecified. IDispatch interfaces can use this flag.
PARAMFLAG_FIN 	Parameter passes information from the caller to the callee.
PARAMFLAG_FOUT 	Parameter returns information from the callee to the caller.
PARAMFLAG_FLCID 	Parameter is the LCID of a client application.
PARAMFLAG_FRETVAL 	Parameter is the return value of the member.
PARAMFLAG_FOPT 	Parameter is optional. The pPARAMDescEx field contains a pointer to a VARIANT describing the default value for this parameter, if the PARAMFLAG_FOPT and PARAMFLAG_FHASDEFAULT bit of wParamFlags is set.
PARAMFLAG_FHASDEFAULT 	Parameter has default behaviors defined. The pPARAMDescEx field contains a pointer to a VARIANT that describes the default value for this parameter, if the PARAMFLAG_FOPT and PARAMFLAG_FHASDEFAULT bit of wParamFlags is set.

typedef enum tagVARFLAGS {
      VARFLAG_FREADONLY               =0x1
     , VARFLAG_FSOURCE               =0x2
     , VARFLAG_FBINDABLE            =0x4
     , VARFLAG_FREQUESTEDIT         =0x8
     , VARFLAG_FDISPLAYBIND         =0x10
     , VARFLAG_FDEFAULTBIND         =0x20
     , VARFLAG_FHIDDEN               =0x40
     , VARFLAG_FRESTRICTED         =0x80
     , VARFLAG_FDEFAULTCOLLELEM      =0x100
     , VARFLAG_FUIDEFAULT            =0x200
     , VARFLAG_FNONBROWSABLE         =0x400
    , VARFLAG_FREPLACEABLE         =0x800,
    , VARFLAG_FIMMEDIATEBIND         =0x1000
} VARFLAGS;
VARFLAG_FREADONLY 	Assignment to the variable should not be allowed.
VARFLAG_FSOURCE 	The variable returns an object that is a source of events.
VARFLAG_FBINDABLE 	The variable supports data binding.
VARFLAG_FREQUESTEDIT 	When set, any attempt to directly change the property results in a call to IPropertyNotifySink::OnRequestEdit. The implementation of OnRequestEdit determines if the change is accepted.
VARFLAG_FDISPLAYBIND 	The variable is displayed to the user as bindable. VARFLAG_FBINDABLE must also be set.
VARFLAG_FDEFAULTBIND 	The variable is the single property that best represents the object. Only one variable in type information can have this attribute.
VARFLAG_FHIDDEN 	The variable should not be displayed to the user in a browser, although it exists and is bindable.
VARFLAG_FRESTRICTED 	The variable should not be accessible from macro languages. This flag is intended for system-level variables or variables that you do not want type browsers to display.
VARFLAG_FDEFAULTCOLLELEM 	Permits an optimization in which the compiler looks for a member named "xyz" on the type of abc. If such a member is found and is flagged as an accessor function for an element of the default collection, then a call is generated to that member function. Permitted on members in dispinterfaces and interfaces; not permitted on modules.
VARFLAG_FUIDEFAULT 	The variable is the default display in the user interface.
VARFLAG_FNONBROWSABLE 	The variable appears in an object browser, but not in a properties browser.
VARFLAG_FREPLACEABLE 	Tags the interface as having default behaviors.
VARFLAG_FIMMEDIATEBIND 	The variable is mapped as individual bindable properties.
 
typedef enum tagVARKIND {
   VAR_PERINSTANCE,
   VAR_STATIC,
   VAR_CONST,
   VAR_DISPATCH
} VARKIND;
VAR_PERINSTANCE 	The variable is a field or member of the type. It exists at a fixed offset within each instance of the type.
VAR_STATIC 	There is only one instance of the variable.
VAR_CONST 	The VARDESC describes a symbolic constant. There is no memory associated with it.
VAR_DISPATCH 	The variable can only be accessed through IDispatch::Invoke.

typedef enum tagTYPEFLAGS {
     TYPEFLAG_FAPPOBJECT =            0x01
   , TYPEFLAG_FCANCREATE =         0x02
   , TYPEFLAG_FLICENSED =            0x04
   , TYPEFLAG_FPREDECLID =         0x08
   , TYPEFLAG_FHIDDEN =            0x10
   , TYPEFLAG_FCONTROL =            0x20
   , TYPEFLAG_FDUAL =               0x40
   , TYPEFLAG_FNONEXTENSIBLE =      0x80
   , TYPEFLAG_FOLEAUTOMATION =      0x100
   , TYPEFLAG_FRESTRICTED =         0x200
   , TYPEFLAG_FAGGREGATABLE =       0x400
 , TYPEFLAG_FREPLACEABLE =          0x800
   , TYPEFLAG_FDISPATCHABLE =       0x1000
 , TYPEFLAG_FREVERSEBIND =          0x2000
   , TYPEFLAG_FPROXY =             0x4000
#ifdef _MAC
 , FUNCFLAG_FORCELONG  =       2147483647
#endif
} TYPEFLAGS;
 

Value 	Description
TYPEFLAG_FAPPOBJECT 	A type description that describes an Application object.
TYPEFLAG_FCANCREATE 	Instances of the type can be created by ItypeInfo::CreateInstance.
TYPEFLAG_FLICENSED 	The type is licensed.
TYPEFLAG_FPREDECLID 	The type is predefined. The client application should automatically create a single instance of the object that has this attribute. The name of the variable that points to the object is the same as the class name of the object.
TYPEFLAG_FHIDDEN 	The type should not be displayed to browsers.
TYPEFLAG_FCONTROL 	The type is a control from which other types will be derived, and should not be displayed to users.
TYPEFLAG_FDUAL 	The interface supplies both IDispatch and VTBL binding.
TYPEFLAG_FNONEXTENSIBLE 	The interface cannot add members at run time.
TYPEFLAG_FOLEAUTOMATION 	The types used in the interface are fully compatible with Automation, including VTBL binding support. Setting dual on an interface sets this flag in addition to TYPEFLAG_FDUAL. Not allowed on dispinterfaces.
TYPEFLAG_FRESTRICTED 	Should not be accessible from macro languages. This flag is intended for system-level types or types that type browsers should not display.
TYPEFLAG_FAGGREGATABLE 	The class supports aggregation.
TYPEFLAG_FDISPATCHABLE 	Indicates that the interface derives from Idispatch, either directly or indirectly. This flag is computed. There is no Object Description Language for the flag.
TYPEFLAG_FPROXY 	Interfaces can be marked with this flag to indicate that they will be using a proxy/stub dynamic link library. This flag specifies that the typelib proxy should not be unregistered when the typelib is unregistered.

TYPEFLAG_FAPPOBJECT can be used on type descriptions with
TypeKind = TKIND_COCLASS, and indicates that the type description specifies an Application object.

Members of the Application object are globally accessible. The Bind method of the ITypeComp instance associated with the library binds to the members of an Application object, just as it does for type descriptions that have
TypeKind = TKIND_MODULE.

The type description implicitly defines a global variable with the same name and type described by the type description. This variable is also globally accessible. When Bind is passed the name of an Application object, a VARDESC is returned, which describes the implicit variable. The ID of the implicitly created variable is always ID_DEFAULTINST.

The ITypeInfo::CreateInstance function of an Application object type description is called, and then it uses GetActiveObject to retrieve the Application object. If GetActiveObject fails because the application is not running, then CreateInstance calls CoCreateInstance, which should start the application.

When TYPEFLAG_FCANCREATE is True, ITypeInfo::CreateInstance can create an instance of the type. This is currently true only for component object classes for which a globally unique identifier (GUID) has been specified.
typedef enum tagTYPEKIND {
     TKIND_ENUM = 0
   , TKIND_RECORD
   , TKIND_MODULE
   , TKIND_INTERFACE
   , TKIND_DISPATCH
   , TKIND_COCLASS
   , TKIND_ALIAS
   , TKIND_UNION
   , TKIND_MAX
} TYPEKIND;
TKIND_ALIAS 	A type that is an alias for another type.
TKIND_COCLASS 	A set of implemented component object interfaces.
TKIND_DISPATCH 	A set of methods and properties that are accessible through IDispatch::Invoke. By default, dual interfaces return TKIND_DISPATCH.
TKIND_ENUM 	A set of enumerators.
TKIND_INTERFACE 	A type that has virtual and pure functions.
TKIND_MODULE 	A module that can only have static functions and data (for example, a DLL).
TKIND_RECORD 	A structure with no methods.
TKIND_UNION 	A union, all of whose members have an offset of zero.
TKIND_MAX 	End of ENUM marker.
 */    
}