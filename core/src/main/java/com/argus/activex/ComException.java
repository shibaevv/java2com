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
 * @version                   $Revision: 1.2 $
 */

public class ComException extends RuntimeException {

    /**
     * 
     */
    private static final long serialVersionUID = -1273433102211257199L;
    private int hr;
    private String source;
    private String helpFile;
    private int helpContext;

    
    public ComException(int hr) {
        super();
        init( hr, null, null, 0);
    }
    public ComException(int hr, String description, String source, String helpFile, int helpContext) {
        super(description);
        init( hr, source, helpFile, helpContext);
    }
    public ComException(String description) {
        this( 0, description, null, null, 0);
    }
    public ComException(int hr, String description) {
        this( hr, description, null, null, 0);
    }
    public ComException(ComException ex) {
        this( ex.hr, null, ex.source, ex.helpFile, ex.helpContext);
    }
    public ComException(ComException ex, String description) {
        this( ex.hr, description, ex.source, ex.helpFile, ex.helpContext);
    }

    private void init(int hr, String source, String helpFile, int helpContext) {
        this.hr = hr;
        this.source = source;
        this.helpFile = helpFile;
        this.helpContext = helpContext;
        
        //System.err.println( "ComException: " + toString() );
    }

    
    public String toString() {
    	return
    		Integer.toHexString(hr).toUpperCase() + ", " + getMessage() + ", " + source + ", " + helpFile + ", " + helpContext;
    }
    
    
    public int getHResult() { 
        return hr;
    }

    public int getHelpContext() {
        return helpContext;
    }

    public String getHelpFile() {
        return helpFile;
    }

    public String getMessage() {
        return super.getMessage();
    }

    public String getSource() {
        return source;
    }

}