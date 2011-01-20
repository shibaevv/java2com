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
 * @version                   $Revision: 1.8 $
 */

import java.awt.Component;
import java.util.ArrayList;
import java.util.EventListener;
import java.util.List;

public class Dispatch {
    
    static {
        // loading a native lib in a static initializer ensures that it is
        // available done before any method in this class is called:
        try {
            DispatchUtils.loadLibrary();
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    private static final ThreadLocal tlDispatch = new ThreadLocal();
    private static final Dispatch [] EMPTY_ARRAY = new Dispatch[0];
	
    // pointer to IDispatch interface (retrived by JNI call)
    private int pDispatch;
    
    // TODO: Not used.
    private int pCEventListener;

    // for Dispatch object(s) created in result of Invoke method
    private Dispatch [] childrenDispatch = EMPTY_ARRAY;
    private int currentChildID;

    public int getDispatch() { return pDispatch; }
    
    protected int CreateObjectCOM(String clsid) throws ComException {
    	return CreateObjectCOM( clsid, COMConstants.CLSCTX_SERVER );
    }
    protected synchronized native int CreateObjectCOM(String clsid, int clsctx) throws ComException;

    protected int CreateObjectDCOM(String clsid, String server) {
    	return CreateObjectDCOM( clsid, server, COMConstants.CLSCTX_SERVER );
    }
    protected synchronized native int CreateObjectDCOM(String clsid, String server, int clsctx) throws ComException;

    /**
     * 
     * @param clsid PROGID or UUID of ActiveX control.
     * @param hwnd
     * @return
     */
    protected synchronized native int CreateObjectCanvas(String clsid, int canvasHWND);

    private synchronized native int ReleaseObject();

    //public synchronized native void Invoke_propget(int dispMethodID, int j, Variant variant);

    //public synchronized native void Invoke_propput(int dispMethodID, Variant variant, int j);

    protected synchronized native int AddListener(int dispMethodID, String s, EventListener eventlistener, String s1);

    protected synchronized native void RemoveListener(int dispMethodID);

    
    /**
     * Takes string id.
     * @param s CLSID/PROGID
     */
    protected Dispatch(String clsid) {
    	init(CreateObjectCOM(clsid));
    }

    /**
     * Will use pointer to IDispatch (retrived by JNI call)
     * @param value
     */
    protected Dispatch(int value) {
        init( value );
    }

    /**
     * Will use pointer to IDispatch (retrived by JNI call)
     * @param value
     */
    protected Dispatch(Number value) {
   		init( value.intValue() );
    }

    /**
     * Will use pointer to IDispatch (retrived by JNI call)
     * @param value
     */
    protected Dispatch(Dispatch value) {
        init( value.getDispatch() );
        //this.pDispatch = value.getDispatch();
    }

    /**
     * Will use pointer to IDispatch (retrived by JNI call)
     * @param value
     */
    protected Dispatch(Variant value) {
        //this( value.intVal() );
        this.pDispatch = value.intVal();
    }

    /**
     * @deprecated
     * Will use pointer to IDispatch (retrived by JNI call)
     * @param value
     */
    protected Dispatch(Object value) {
        if (value instanceof String)
            init( CreateObjectCOM((String) value) );
        if (value instanceof Number)
            init(((Number) value).intValue());
        if (value instanceof Dispatch)
            init(((Dispatch) value).getDispatch());
        if (value instanceof Variant)
            init(((Variant) value).intVal());
        
    }

    /**
     * TODO: Attach an ActiveX control as a child of the HWND (retrived by ActiveXCanvas).
     * @param clsid
     * @param canvasHWND
     */
    protected Dispatch(String clsid, int canvasHWND) {
    	init(CreateObjectCanvas(clsid, canvasHWND));
    }
    public Dispatch(String clsid, Component canvas) {
        this(clsid, DispatchUtils.getHWND(canvas));
    }

    /**
     * TODO: Will instantiate remote server.
     * @param clsid
     * @param server
     */
    protected Dispatch(String clsid, String server) {
    	init( CreateObjectDCOM(clsid, server) );
    }

    public int hashCode() {
        return pDispatch;
    }
    
    public boolean equals(Object obj) {
        if (obj instanceof Dispatch) {
            return pDispatch == ((Dispatch) obj).pDispatch;
        }
        return super.equals(obj);
    }

    public String toString() {
        return getClass().getName() + " " + Integer.toHexString(pDispatch).toUpperCase();
    }
    
    /**
     * Common initializer
     * Will use pointer to IDispatch (retrived by JNI call)
     * @param pDispatch
     */
    private void init(int pDispatch) {

    	// init pDispatch
    	this.pDispatch = pDispatch;
    	//print();

    	// add this to tlDispatch
        List list = (List) tlDispatch.get();
    	if (list == null) {
            list = new ArrayList();
    		tlDispatch.set(list);
    	}
        if (!list.contains(this)) {
            list.add(this);
//            if (DispatchUtils.DEBUG) System.out.println(list.size() + " Dispatch object stored (" + this + ")" );
        }
    	
    }
    
    private synchronized native void Invoke(int dispMethodID, Variant [] avariant, int j, short wInvokeFlag, Variant output)
        throws ComException;

    /**
     * @deprecated
     * @param dispMethodID
     * @param clsid
     * @param avariant
     * @param j
     * @param wInvokeFlag
     * @param output
     * @throws ComException
     */
    private synchronized native void InvokeCLSID(int dispMethodID, String clsid, Variant [] avariant, int j, short wInvokeFlag, Variant output)
        throws ComException;

    protected Variant invoke_method(Variant [] avariant, int dispMethodID, short wInvokeFlag) {
    	Variant output = new Variant();
        //System.out.println("invoke_method(pDispatch=" + pDispatch);
        Invoke(pDispatch, avariant, dispMethodID, wInvokeFlag, output);
        //updateContainedDispatch(output);
        return output;
    }

    protected void invoke_method_void(Variant [] avariant, int dispMethodID, short wInvokeFlag) {
        //System.out.println("invoke_method_void(pDispatch=" + pDispatch);
    	Invoke(pDispatch, avariant, dispMethodID, wInvokeFlag, null);
    }

    /**
     * @deprecated
     * @param avariant
     * @param dispMethodID
     * @param clsid
     * @param wInvokeFlag
     * @return
     */
    protected Variant invoke_method_clsid(Variant [] avariant, int dispMethodID, String clsid, short wInvokeFlag) {
    	Variant output = new Variant();
        InvokeCLSID(pDispatch, clsid, avariant, dispMethodID, wInvokeFlag, output);
        //updateContainedDispatch(output);
        return output;
    }
    
    /**
     * Release reference count for this COM object by ONE.
     * @return reference count for this COM object
     */
    public synchronized int releaseObject() {
        if (pDispatch == 0) 
            return 0;
        
        try {
            //releaseContainedDispatch();
            
            int refCount = ReleaseObject();
            if (DispatchUtils.DEBUG) System.out.println( "\trefCount=" + refCount );
            return refCount;
            
        } finally {
            pDispatch = 0;
        }
        
    }
    
    private void updateContainedDispatch(Variant output) {
        //if (true) return;
        short vt = output.getvt();
        if (!(vt == COMConstants.VT_DISPATCH || 
        	 vt == (COMConstants.VT_DISPATCH|COMConstants.VT_BYREF)))
        	return;
        
    	if (childrenDispatch.length == 0) {
    		childrenDispatch = new Dispatch[2];
    		currentChildID = 0;
    	}
    	int length = childrenDispatch.length;
    	if (length == currentChildID) {
            Dispatch [] containedDispatch2 = new Dispatch [length * 2];
    		System.arraycopy(childrenDispatch, 0, containedDispatch2, 0, length);
    		childrenDispatch = containedDispatch2;
    	}
        Dispatch pDisp = output.DispatchVal();
    	childrenDispatch[currentChildID] = pDisp;
//        if (DispatchUtils.DEBUG) System.out.println(containedID + " Contained ( " + pDisp + " )" );
        currentChildID++;
    }

    private void releaseContainedDispatch() {
        List list = (List) tlDispatch.get();
        for (int i = 0; i < childrenDispatch.length; i++) {
            Dispatch pContainedDispatch = childrenDispatch[i];
            if (pContainedDispatch == null) continue;
            //if (pContainedDispatch.getClass().equals(Dispatch.class)) continue;
            if (DispatchUtils.DEBUG) System.out.println("ReleaseObject(" + pContainedDispatch + ")");
            
            pContainedDispatch.releaseObject();
            childrenDispatch[i] = null;
        }
        childrenDispatch = EMPTY_ARRAY;
        
        if (list != null) {
            list.remove(this);
            if (DispatchUtils.DEBUG) System.out.println( list.size() + " Dispatch objects left." );
        }
        
    }
/*
    protected Variant invoke_propget(int dispMethodID) {
        Variant variant = new Variant();
        IDispatch_Invoke_propget(pDispatch, dispMethodID, variant);
        if (DispatchUtils.DEBUG) System.out.println("propget - " + variant);
        return variant;
    }

    protected void invoke_propput(Variant variant, int dispMethodID) {
        IDispatch_Invoke_propput(pDispatch, variant, dispMethodID);
    }
*/
    public void addListener(String s, EventListener eventlistener) {
    	String s1 = eventlistener.getClass().getSuperclass().getName();
        int i = s1.lastIndexOf(".");
        String s2 = s1.substring(0, i);
        pCEventListener = AddListener(pDispatch, s, eventlistener, s2);
    }

    public void removeListener(String s, EventListener eventlistener) {
    	RemoveListener(pCEventListener);
    }

}