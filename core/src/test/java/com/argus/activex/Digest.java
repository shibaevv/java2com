package com.argus.activex;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Digest
{

    private static final String MD5 = "MD5";

    /** Creates a new instance of Digest */
    private Digest()
    {
        super();
    }

    public static String digest(String value)
    {
        try
        {
            return digest(value, MD5);
        }
        catch (NoSuchAlgorithmException e)
        {
            e.printStackTrace();
            return null;
        }
    }

    public static String digest(String value, String algorithm) throws NoSuchAlgorithmException
    {
        MessageDigest md = MessageDigest.getInstance(algorithm);

        byte[] output = md.digest(value.getBytes());
        md.reset();

        //logger.info(value + ":" + toHexString( output ));
        return StringUtils.toHexString(output);
    }

    public static void main(String[] args) throws Exception
    {
        System.out.println(Digest.digest(
            "", Digest.MD5));
    }

}