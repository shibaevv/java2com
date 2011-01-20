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

import java.util.Calendar;
import java.util.Date;

public class Variant {
    
    public static final Variant [] EMPTY_ARRAY = new Variant [0];
    
    // read/write by jni code (in dll)
    private int pVariant;
    
    public Variant() {
        init();
        putEmpty();
    }

    public Variant( boolean value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( boolean value, short vt ) {
        init();
        putBoolean(value, false);
    }
    public Variant( Boolean value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( Boolean value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else putBoolean( (Boolean) value, false );
    }

    public Variant( byte value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( byte value, short vt ) {
        init();
        putByte(value, false);
    }
    public Variant( Byte value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( Byte value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else putByte( value, false );
    }

    public Variant( short value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( short value, short vt ) {
        init();
        putShort(value, false);
    }
    public Variant( Short value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( Short value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else putShort( value, false );
    }

    public Variant( int value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( int value, short vt ) {
        init();
        putInt(value, false);
    }
    public Variant( Integer value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( Integer value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else putInt( value, false );
    }

    public Variant( long value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( long value, short vt ) {
        init();
        putCurrency(value, false);
    }
    public Variant( Long value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( Long value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else putCurrency(value, false);
    }

    public Variant( float value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( float value, short vt ) {
        init();
        putFloat( value, false );
    }
    public Variant( Float value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( Float value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else putFloat( value, false );
    }

    public Variant( double value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( double value, short vt ) {
        init();
        putDouble(value, false);
    }
    public Variant( Double value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( Double value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else putDouble( value, false );
    }

    public Variant( String value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( String value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else putString( (String) value, false );
    }

    public Variant( Object value, int vt ) {
        this(value, (short) vt);
    }
    public Variant( Object value, short vt ) {
        init();
        if ( value == null ) putEmpty();
        else if (value instanceof Dispatch) putDispatch( (Dispatch) value, false );
        else if (value instanceof Boolean) putBoolean( (Boolean) value, false );
        else if (value instanceof Byte) putByte( (Byte) value, false );
        else if (value instanceof Integer) putInt( (Integer) value, false );
        else if (value instanceof Long) putCurrency( (Long) value, false );
        else if (value instanceof Float) putFloat( (Float) value, false );
        else if (value instanceof Double) putDouble( (Double) value, false );
        else if (value instanceof Date) putDate( (Date) value, false );
        else if (value instanceof String) putString( (String) value, false );
        else 
            throw new ComException("UNHANDLED -> " + value.getClass().getName());
    }

    // call this to explicitly release the com object before gc
    private native void release();

    protected native void init();
    
//*
    protected void finalize() throws Throwable {
        release();
        super.finalize(); // do nothing
    }
//*/
    
    public native void VariantClear();

    
    //public native void changeType( short vt );
    //public void changeType( int vt ) { changeType( (short) vt ); }

    
    public native short getvt();


    public native void noParam();


    public native void putEmpty();
    public native void putBoolean( boolean in, boolean byRef );
    public void putBoolean( Boolean in, boolean byRef ) { putBoolean(in.booleanValue(), byRef); }
    public native void putByte( byte in, boolean byRef );
    public void putByte( Byte in, boolean byRef ) { putByte(in.byteValue(), byRef); }
    public native void putShort( short in, boolean byRef );
    public void putShort( Short in, boolean byRef ) { putShort(in.shortValue(), byRef); }
    public native void putInt( int in, boolean byRef );
    public void putInt( Integer in, boolean byRef ) { putInt(in.intValue(), byRef); }
    public native void putCurrency( long in, boolean byRef ); // Currency
    public void putCurrency( Long in, boolean byRef ) { putCurrency(in.longValue(), byRef); } // Currency
    public native void putFloat( float in, boolean byRef );
    public void putFloat( Float in, boolean byRef ) { putFloat(in.floatValue(), byRef); }
    public native void putDouble( double in, boolean byRef );   
    public void putDouble( Double in, boolean byRef ) { putDouble(in.doubleValue(), byRef); }   
    public native void putDate( double in, boolean byRef );
    public void putDate( Date in, boolean byRef ) { putDate(convertJavaDate2VariantDate(in), byRef); }
    public native void putString( String in, boolean byRef );
    public native void putError( int in, boolean byRef );
    public native void putDispatch( Dispatch in, boolean byRef );


    public native void getNull();
    public native void getEmpty();
    public native boolean getBoolean( boolean byRef );
    public native byte getByte( boolean byRef );
    public native short getShort( boolean byRef );
    public native int getInt( boolean byRef );
    public native long getCurrency( boolean byRef ); // Currency
    public native float getFloat( boolean byRef );
    public native double getDouble( boolean byRef );
    public native double getDate( boolean byRef );
    public native String getString( boolean byRef );
    public native int getError( boolean byRef );
    public Object getObject( boolean byRef ) { return toObject(); }
    public Dispatch getDispatch( boolean byRef ) { return toDispatch(); }

    
    public boolean booleanVal() { return getBoolean( false ); }
    public byte byteVal() { return getByte( false ); }
    public short shortVal() { return getShort( false ); }
    public int intVal() { return getInt( false ); }
    public long longVal() { return getCurrency( false ); } // Currency
    public float floatVal() { return getFloat( false ); }
    public double doubleVal() { return getDouble( false ); }
    public Date DateVal() { return convertVariantDate2JavaDate( getDate( false ) ); }
    public String StringVal() { return getString( false ); }
    public Dispatch DispatchVal() { return getDispatch( false ); }
    public Object ObjectVal() { return getObject( false ); }

    
    // is the variant null or empty or error or null disp 
    public native boolean isNull();
    // change variant type
    public native boolean toBoolean();
    public native byte toByte();
    public native short toShort();
    public native int toInt();
    public native float toFloat();
    public native double toDouble();
    public native long toCurrency();
    public native double toDate();
    public native String toString();
    public native int toError();
    //public Object toScriptObject() { return toDispatch(); }
    public native Dispatch toDispatch();

    public Object toObject()
    {
		int vt = (int)getvt() & 0xFFFFDFFF;
		//System.out.println("Variant.java:  Handle vt  - " + vt);
        switch(vt)
        {
	        case COMConstants.VT_EMPTY :
	        case COMConstants.VT_NULL :
	            return null;//new Object();
	
	        case COMConstants.VT_BOOL :
	        	return booleanVal() ? Boolean.TRUE : Boolean.FALSE;
	
			case COMConstants.VT_I1 :
			case COMConstants.VT_UI1 :
				return new Byte(toByte());

	        case COMConstants.VT_I2 :
	        case COMConstants.VT_UI2 :
	        	return new Short(toShort());
	
	        case COMConstants.VT_I4 :
	        case COMConstants.VT_UI4 :
	        case COMConstants.VT_INT :
	        case COMConstants.VT_UINT :
	        	return new Integer(toInt());
	
	        case COMConstants.VT_R4 :
	        	return new Float(toFloat());
	
	        case COMConstants.VT_R8 :
	        	return new Double(toDouble());
	
			case COMConstants.VT_CY :
				return new Long( toCurrency() );
	
			case COMConstants.VT_BSTR :
				return toString();
			
	        case COMConstants.VT_DATE :
	        	return new Double(toDate());
			
			//case COMConstants.VT_VARIANT :
			//	return ;
				
			case COMConstants.VT_DISPATCH :
	        	return toDispatch();
	
	        default:
	            System.err.println("Variant.java: Unhandled vt: [" + vt + "]");
	        	return null;
        }

    }

    public static final long SECONDS_PER_DAY = 24 * 60 * 60;
    public static final long MILLIS_PER_DAY = SECONDS_PER_DAY * 1000L;
    public static final Date VARIANT_ZERO_DATE;
    public static final Date JAVA_ZERO_DATE;
    static {
        Calendar calendar = Calendar.getInstance();
        calendar.set( Calendar.YEAR, 1899 );
        calendar.set( Calendar.MONTH, 11 );
        calendar.set( Calendar.DAY_OF_MONTH, 30 );
        VARIANT_ZERO_DATE = calendar.getTime(); 
        calendar.set( Calendar.YEAR, 1970 );
        calendar.set( Calendar.MONTH, 0 );
        calendar.set( Calendar.DAY_OF_MONTH, 1 );
        JAVA_ZERO_DATE = calendar.getTime();
    }
    public static long JAVA_VARIANT_TIME_DIFF = JAVA_ZERO_DATE.getTime() - VARIANT_ZERO_DATE.getTime();
    public static long JAVA_VARIANT_DAY_DIFF  = JAVA_VARIANT_TIME_DIFF / MILLIS_PER_DAY;

    // TODO: use excel-date converter methods ???
    public static Date convertVariantDate2JavaDate(double msDate) { 
        long ms = (long) ( msDate * MILLIS_PER_DAY ) - JAVA_VARIANT_TIME_DIFF;
        Calendar calendar = Calendar.getInstance();
        calendar.setTimeInMillis(ms);
        long ZONE_OFFSET = calendar.get(Calendar.ZONE_OFFSET);
        long DST_OFFSET = calendar.get(Calendar.DST_OFFSET);
        long dtd = ZONE_OFFSET + DST_OFFSET;
        return new Date( ms - dtd );
    }
    public static double convertJavaDate2VariantDate(Date date) { 
        //TIME_ZONE_INFORMATION timeinfo;
        //GetTimeZoneInformation(&timeinfo);
        //return val / (24*60*60*1000.) + 25569.0 - (timeinfo.Bias/(60.0*24.0));
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date);
        long ZONE_OFFSET = calendar.get(Calendar.ZONE_OFFSET);
        long DST_OFFSET = calendar.get(Calendar.DST_OFFSET);
        long dtd = ZONE_OFFSET + DST_OFFSET;
        return (double) ( date.getTime() + JAVA_VARIANT_TIME_DIFF + dtd ) / MILLIS_PER_DAY;
    }
    
}