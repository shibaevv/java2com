//---------------------------------------------------------------------------

#ifndef jni_utilsH
#define jni_utilsH

#include <jni.h>

#include <windows.h>
//#include <wtypes.h>

#define VARIANT_FLD "pVariant"
#define DISP_FLD "pDispatch"

class Constants {
public:
	static HINSTANCE hInstance;
	static HANDLE hModule;
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

VARIANT * extractVariant(JNIEnv *env, jobject arg);
// extract a pDispatch from a jobject
jint extractPDispatch(JNIEnv *env, jobject arg);
// extract a IDispatch from a jobject
IDispatch * extractDispatch(JNIEnv *env, jobject arg);


VARTYPE getVarType(JNIEnv * env, jobject jvariant);

jboolean getBooleanValue(JNIEnv * env, jobject jvariant);
void setBooleanValue( JNIEnv * env, jobject jvariant, jboolean value );

jbyte getByteValue(JNIEnv * env, jobject jvariant);
void setByteValue(JNIEnv * env, jobject jvariant, byte value);
void setFieldValue(JNIEnv *env, jobject obj, const char * name, jbyte value);

short getShortValue(JNIEnv * env, jobject jvariant);
void setShortValue(JNIEnv * env, jobject jvariant, jshort value);
jshort getFieldValueShort(JNIEnv * env, jobject obj, const char * name);
void setFieldValue(JNIEnv *env, jobject obj, const char * name, jshort value);

jint getIntValue(JNIEnv * env, jobject jvariant);
void setIntValue(JNIEnv * env, jobject jvariant, jint value);
void setFieldValue(JNIEnv *env, jobject obj, const char * name, jint value);

jlong getLongValue(JNIEnv * env, jobject jvariant);
void setLongValue( JNIEnv * env, jobject jvariant, jlong value );
void setFieldValue(JNIEnv *env, jobject obj, const char * name, jlong value);

float getFloatValue(JNIEnv * env, jobject jvariant);
void setFloatValue( JNIEnv * env, jobject jvariant, float value );

double getDoubleValue(JNIEnv * env, jobject jvariant);
void setDoubleValue( JNIEnv * env, jobject jvariant, double value );

jstring getStringValue(JNIEnv * env, jobject jvariant);
void setStringValue( JNIEnv * env, jobject jvariant, wchar_t * value );
void setFieldValue( JNIEnv * env, jobject obj, const char * name, jstring value );

jobject getObjectValue(JNIEnv * env, jobject jvariant);
jobject getObjectFieldValue(JNIEnv * env, jobject obj, const char * name, const char * sig);
void    setObjectFieldValue(JNIEnv * env, jobject obj, const char * name, const char * sig, jobject value);

jboolean isNull(JNIEnv * env, jobject jvariant);

jsize getArrayLength( JNIEnv * env, jarray params );

jstring NewString( JNIEnv *env, const wchar_t * bs );

void ThrowComException( JNIEnv * env, jint hr, const char * desc );
void ThrowComException( JNIEnv * env, jint hr, const wchar_t * desc,
   const wchar_t * source, const wchar_t * helpFile, jint helpContext );

void ThrowDAQException( JNIEnv * env, const char * message );


jmethodID GetCTORMethodID(JNIEnv * env,
   jclass clazz,
   const char * sig = "()V");

jmethodID GetCTORMethodID(JNIEnv * env,
   const char * className,
   const char * sig = "()V");


jmethodID GetMethodID(JNIEnv * env,
   jclass clazz,
   const char * name,
   const char * sig = "()V");

jmethodID GetMethodID(JNIEnv * env,
   const char * className,
   const char * name,
   const char * sig = "()V");

//---------------------------------------------------------------------------
#endif
