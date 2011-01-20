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

import java.awt.Component;
import java.util.HashMap;
import java.util.Map;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Argus Software Pty Ltd</p>
 * @author Valeri SHIBAEV
 * @author Last Updated By:   $Author: Valera $
 * @version                   $Revision: 1.6 $
 */

public class DispatchUtils implements COMConstants {
    
    static boolean DEBUG = 
        //true;
        "true".equalsIgnoreCase( System.getProperty("debug") );
    
    static {
        loadLibrary();        
    }

    private final static Map WINERRORS = new HashMap();
    static {
        WINERRORS.put("8000FFFF", "Catastrophic failure. E_UNEXPECTED (0x8000FFFFL)");
        WINERRORS.put("8001010E", "The application called an interface that was marshalled for a different thread. RPC_E_WRONG_THREAD (0x8001010EL)");
        WINERRORS.put("80020009", "Exception occurred. DISP_E_EXCEPTION (0x80020009L)");
        WINERRORS.put("80040154", "Class not registered. REGDB_E_CLASSNOTREG (0x80040154L)");
        WINERRORS.put("800401F0", "CoInitialize has not been called. CO_E_NOTINITIALIZED (0x800401F0L)");
    }
    
    /**
     * Package level method.
     */
    static void loadLibrary() {
        final String LIBRARY_NAME = "java2com";
        final String JAVA_LIBRARY_PATH = "java.library.path";
        
        // loading a native lib in a static initializer ensures that it is
        // available done before any method in this class is called:
        try {
            //System.setProperty( JAVA_LIBRARY_PATH, 
            //    LIBRARY_PATH + java.io.File.pathSeparatorChar + System.getProperty( JAVA_LIBRARY_PATH ) );
            //System.mapLibraryName(  );
            
            java.lang.System.loadLibrary( LIBRARY_NAME );
            java.lang.System.out.println( "native lib '" + LIBRARY_NAME + "' successfully loaded." );

        } catch ( java.lang.UnsatisfiedLinkError ex ) {
            java.lang.System.err.println(
                ex.getMessage() + 
                "\nnative lib '" + LIBRARY_NAME + 
                "' not found in '" + // JAVA_LIBRARY_PATH + "': " + 
                java.lang.System.getProperty( JAVA_LIBRARY_PATH ) 
            );
            
            throw ex; // re-throw
        }
        
    }
    
    /**
     * Error code definitions for the Win32 API functions (winerror.h)
     * @param hresult
     * @return
     */
    public static String getErrorDescription(int hresult) {
        String error = (String) WINERRORS.get(Integer.toHexString(hresult).toUpperCase());
        if (error == null)
            error = "UNKNOWN HRESULT: " + Integer.toHexString(hresult).toUpperCase();
        return error;
    }

    /**
     * Error code definitions for the Win32 API functions (winerror.h)
     * @param ex
     * @return
     */
    public static String getErrorDescription(ComException ex) {
        return getErrorDescription(ex.getHResult());
    }
    
    public static synchronized String getJava2COMVersion() throws ComException {
    	return GetJava2COMVersion();
	}

    public static synchronized boolean isServerRunning(String clsid) throws ComException {
    	return IsServerRunning(clsid);
    }

    public static synchronized int getActiveObject(String clsid) throws ComException {
    	return GetActiveObject(clsid);
	}

    /**
     * Return the HWND for the Java Heavy Weight Component.
     * Also you should call this only after addNotify() has been called.
     * @return the HWND for the AWT Component.
     */
    public static synchronized int getHWND(Component canvas) throws ComException {
        return GetHWND(canvas);
    }

    public static synchronized void resizeControl(int hwnd, int width, int height) throws ComException {
        ResizeControl(hwnd, width, height);
    }
    public static synchronized void resizeControl(Component canvas, int width, int height) throws ComException {
        ResizeControl(GetHWND(canvas), width, height);
    }

    private static native String GetJava2COMVersion() throws ComException;
    private static native boolean IsServerRunning(String clsid) throws ComException;
    private static native int GetActiveObject(String clsid) throws ComException;
    private static native int GetHWND(Component canvas);
    private static native void ResizeControl(int hwnd, int width, int height);

 }