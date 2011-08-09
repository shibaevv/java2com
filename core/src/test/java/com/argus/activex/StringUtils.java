/*
 *              Argus Software Pty Ltd License Notice
 * 
 * The contents of this file are subject to the Argus Software Pty Ltd
 * License Version 1.0 (the "License"). 
 * You may not use this file except in compliance with the License.
 * A updated copy of the License is available at
 * http://www.argussoftware.net/license/license_agreement.html
 * 
 * The Original Code is argus. The Initial Developer of the Original
 * Code is Argus Software Pty Ltd, All Rights Reserved.
 */

package com.argus.activex;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.lang.reflect.Method;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Argus Software Pty Ltd</p>
 * @author Valeri SHIBAEV
 * @author Last Updated By:   $Author: Valera $
 * @version                   $Revision: 1.3 $
 */

public final class StringUtils {

    private static final char [] hexChars = 
        { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    private static final String  hexString = new String(hexChars);

    /**
	 * 
	 */
	private StringUtils() {}

    /**
     * Converts a byte array to hex string
     */
    public static String toHexString( byte [] block ) {
        if (block == null) {
            return null;
        }

        int len = block.length;
        StringBuffer buf = new StringBuffer( len * 2 );

        for ( int i = 0; i < len; i++ )
             byte2hex( block[i], buf );
    
        return buf.toString();

    }
    
    /**
     * Converts an object to hex string
     * @throws IOException 
     */
    public static String toHexString( Object obj )
        throws IOException 
    {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        //IOUtils.writeObject(obj, baos);
        ObjectOutputStream out = new ObjectOutputStream( baos );
        try { out.writeObject(obj); }
        finally { out.close(); }

        return toHexString(baos.toByteArray());      
    }
        
    /**
     * Transforms a hexadecimal string to a byte array.
     *
     * @param str - a hexadecimal string to be transformed
     * @return the byte array, or null if the passed String is null
     * @exception IllegalArgumentException if the passed String is not haxadecimal encoded
     */
    public static byte [] fromHexString(String hex) {
        if (hex == null) {
            return null;
        }
        else if ((hex.length() % 2) != 0) {
            throw new IllegalArgumentException("Hex String length must be a multiple of 2");
        }

        int     length  = hex.length() / 2;
        byte[]  result  = new byte[length];
        String  h       = hex.toUpperCase();
        for (int i = 0; i < length; i++) {
            char c = h.charAt(2 * i);
            int index = hexString.indexOf(c);
            if (index == -1) {
                throw new IllegalArgumentException("Hex String can't contain '" + c + "'");
            }

            int j = 16 * index;
            c = h.charAt((2 * i) + 1);
            index = hexString.indexOf(c);
            if (index == -1) {
                throw new IllegalArgumentException("Hex String can't contain '" + c + "'");
            }

            j += index;

            result[i] = (byte) (j & 0xFF);
        }

        return result;
    }
     
    /*
     * Converts a byte to hex digit and writes to the supplied buffer
     */
    private static void byte2hex( byte b, StringBuffer buf ) {
        int high = (b & 0xf0) >> 4;
        int low = b & 0x0f;
        buf.append( hexChars[high] );
        buf.append( hexChars[low] );
    }

    public final static String toString(Method method) {
        return new StringBuffer()
	        .append(method.getReturnType().getName())
	        .append(method.getName())
	        .append(toString(method.getParameterTypes()))
	        .toString();
    }
    
    public final static String toString(Class [] types) {
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < types.length; i++) {
            sb.append(types[i].getName());
        }
        return sb.toString();
    }

    public static void main(String [] args) {
        String s = toHexString("VAlera Otchen' horoshij Chelovek1".getBytes());
        byte [] b = fromHexString(s);
        System.out.println(new String(b));
    }
    
}
