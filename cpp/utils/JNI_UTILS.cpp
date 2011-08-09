//---------------------------------------------------------------------------

//#pragma hdrstop

#include "stdafx.h"
#include "jni_utils.h"

using namespace std;

HINSTANCE Constants::hInstance = 0;
HANDLE Constants::hModule = 0;

//---------------------------------------------------------------------------
//#pragma package(smart_init)

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

// extract a VARIANT from a Variant object
VARIANT * extractVariant(JNIEnv *env, jobject arg)
{
  jclass clazz = env->GetObjectClass(arg);
  jfieldID ajf = env->GetFieldID( clazz, VARIANT_FLD, "I");
  env->DeleteLocalRef(clazz);
  jint anum = env->GetIntField(arg, ajf);
  VARIANT *v = (VARIANT *)anum;
  return v;
}

// extract a pDispatch from a jobject
jint extractPDispatch(JNIEnv *env, jobject arg)
{
  jclass clazz = env->GetObjectClass(arg);
  jfieldID ajf = env->GetFieldID( clazz, DISP_FLD, "I");
  env->DeleteLocalRef(clazz);
  return env->GetIntField(arg, ajf);
}

// extract a IDispatch from a jobject
IDispatch * extractDispatch(JNIEnv *env, jobject arg)
{
  return (IDispatch *) extractPDispatch(env, arg);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
VARTYPE getVarType(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID( clazz, "getType", "()I" );
   env->DeleteLocalRef(clazz);
   return env->CallIntMethod( jvariant, mid );
}

jboolean getBooleanValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "booleanVal", "()Z" );
   env->DeleteLocalRef(clazz);
   return env->CallBooleanMethod( jvariant, mid );
}
void setBooleanValue( JNIEnv * env, jobject jvariant, jboolean value ) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "booleanVal", "(Z)V" );
   env->DeleteLocalRef(clazz);
   env->CallVoidMethod( jvariant, mid, value );
}

jbyte getByteValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "byteVal", "()B" );
   env->DeleteLocalRef(clazz);
   return env->CallByteMethod( jvariant, mid );
}
void setByteValue( JNIEnv * env, jobject jvariant, jbyte value ) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "byteVal", "(B)V" );
   env->DeleteLocalRef(clazz);
   env->CallVoidMethod( jvariant, mid, value );
}
void setFieldValue(JNIEnv *env, jobject obj, const char * name, jbyte value) {
   jclass clazz = env->GetObjectClass(obj);
   jfieldID jf = env->GetFieldID( clazz, name, "B");
   env->DeleteLocalRef(clazz);
   env->SetByteField(obj, jf, value);
}

short getShortValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "shortVal", "()S" );
   env->DeleteLocalRef(clazz);
   return env->CallShortMethod( jvariant, mid );
}
void setShortValue(JNIEnv * env, jobject jvariant, jshort value ) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "shortVal", "(S)V" );
   env->DeleteLocalRef(clazz);
   env->CallVoidMethod( jvariant, mid, value );
}
jshort getFieldValueShort(JNIEnv * env, jobject obj, const char * name) {
   jclass clazz = env->GetObjectClass(obj);
   jfieldID jf = env->GetFieldID( clazz, name, "S");
   env->DeleteLocalRef(clazz);
   return env->GetShortField( obj, jf );
}
void setFieldValue(JNIEnv *env, jobject obj, const char * name, jshort value) {
   jclass clazz = env->GetObjectClass(obj);
   jfieldID jf = env->GetFieldID( clazz, name, "S");
   env->DeleteLocalRef(clazz);
   env->SetShortField(obj, jf, value);
}

jint getIntValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "intVal", "()I" );
   env->DeleteLocalRef(clazz);
   return env->CallLongMethod( jvariant, mid );
}
void setIntValue(JNIEnv * env, jobject jvariant, jint value) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "intVal", "(I)V" );
   env->DeleteLocalRef(clazz);
   env->CallVoidMethod( jvariant, mid, value );
}
void setFieldValue(JNIEnv *env, jobject obj, const char * name, jint value) {
   jclass clazz = env->GetObjectClass(obj);
   jfieldID jf = env->GetFieldID( clazz, name, "I");
   env->DeleteLocalRef(clazz);
   env->SetIntField(obj, jf, value);
}

jlong getLongValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "longVal", "()J" );
   env->DeleteLocalRef(clazz);
   return env->CallLongMethod( jvariant, mid );
}
void setLongValue( JNIEnv * env, jobject jvariant, jlong value ) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "longVal", "(J)V" );
   env->DeleteLocalRef(clazz);
   env->CallVoidMethod( jvariant, mid, value );
}
void setFieldValue(JNIEnv *env, jobject obj, const char * name, jlong value) {
   jclass clazz = env->GetObjectClass(obj);
   jfieldID jf = env->GetFieldID( clazz, name, "J");
   env->DeleteLocalRef(clazz);
   env->SetLongField(obj, jf, value);
}

float getFloatValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "floatVal", "()F" );
   env->DeleteLocalRef(clazz);
   return env->CallFloatMethod( jvariant, mid );
}
void setFloatValue( JNIEnv * env, jobject jvariant, float value ) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "floatVal", "(F)V" );
   env->DeleteLocalRef(clazz);
   env->CallVoidMethod( jvariant, mid, value );
}

double getDoubleValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "doubleVal", "()D" );
   env->DeleteLocalRef(clazz);
   return env->CallDoubleMethod( jvariant, mid );
}
void setDoubleValue( JNIEnv * env, jobject jvariant, double value ) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "doubleVal", "(D)V" );
   env->DeleteLocalRef(clazz);
   env->CallVoidMethod( jvariant, mid, value );
}

double getDateValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "doubleVal", "()D" );
   env->DeleteLocalRef(clazz);
   return env->CallDoubleMethod( jvariant, mid );
}
void setDateValue( JNIEnv * env, jobject jvariant, double value ) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "doubleVal", "(D)V" );
   env->DeleteLocalRef(clazz);
   env->CallVoidMethod( jvariant, mid, value );
}

jstring getStringValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "StringVal", "()Ljava/lang/String;" );
   env->DeleteLocalRef(clazz);
   //return dynamic_cast<jstring>( env->CallObjectMethod( jvariant, mid ) );
   return (jstring) env->CallObjectMethod( jvariant, mid );
}
void setStringValue( JNIEnv * env, jobject jvariant, wchar_t * value ) {
   // wchar_t to char
   size_t len = wcslen(value);
   char * utf = new char[ len + 1 ];
   bool res = ustrncpy( utf, value, len + 1 );
   if ( !res ) {
//cerr << "setStringValue()\tustrncpy(...) FAILED!" << endl;
   	delete [] utf;
      return;
   }

   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "StringVal", "(Ljava/lang/String;)V" );
   env->DeleteLocalRef(clazz);

   jstring s = env->NewStringUTF( utf );
	delete [] utf;

   env->CallVoidMethod( jvariant, mid, s );
}
void setFieldValue( JNIEnv * env, jobject obj, const char * name, jstring value ) {
   setObjectFieldValue( env, obj, name, "Ljava/lang/String;", value);
}

jobject getObjectValue(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID( clazz, "ObjectVal", "()Ljava/lang/Object;" );
   env->DeleteLocalRef(clazz);
   return env->CallObjectMethod( jvariant, mid );
}
jobject getObjectFieldValue(JNIEnv * env, jobject obj, const char * name, const char * sig) {
   jclass clazz = env->GetObjectClass(obj);
   jfieldID jf = env->GetFieldID( clazz, name, sig);
   env->DeleteLocalRef(clazz);
   return env->GetObjectField(obj, jf);
}
void setObjectFieldValue(JNIEnv * env, jobject obj, const char * name, const char * sig, jobject value) {
   jclass clazz = env->GetObjectClass(obj);
   jfieldID jf = env->GetFieldID( clazz, name, sig);
   env->DeleteLocalRef(clazz);
   env->SetObjectField(obj, jf, value);
}


jboolean isNull(JNIEnv * env, jobject jvariant) {
   jclass clazz = env->GetObjectClass( jvariant );
   jmethodID mid = env->GetMethodID(clazz, "isNull", "()Z" );
   env->DeleteLocalRef(clazz);
   return env->CallBooleanMethod( jvariant, mid );
}

jsize getArrayLength( JNIEnv * env, jarray params ) {
   return env->GetArrayLength( params );
}


jstring NewString( JNIEnv * env, const wchar_t * bs ) {
   if (bs == NULL)
      return NULL;

   size_t len = wcslen(bs);
   //size_t len = SysStringLen(bs);
   char * pData = new char[ len + 1 ];

   jstring js = NULL;
   if ( ustrncpy( pData, bs, len + 1 ) )
      js = env->NewStringUTF( pData );
   delete [] pData;
   return js;

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
/*
 * Class:     com_argus_activex_ComException
 * Method:    ComException
 * Signature: (ILjava/lang/String;)V
 */
void ThrowComException( JNIEnv *env, jint hr, const char * desc )
{
	if (!env) {
		cerr << "ThrowComException: " << hex << hr << " (" << desc << "), but JNIEnv is not set..." << endl;
		return;
	}

	if ( env->ExceptionOccurred() ) {
		cerr << "ThrowComException: " << hex << hr << ", but another ExceptionOccurred before..." << endl;
		return;
	}
	//cerr << "ThrowComException: " << hex << hr << endl;

	jclass clazz = env->FindClass("com/argus/activex/ComException");
	// call the constructor that takes hr and message
	jmethodID ctor = GetCTORMethodID( env, clazz, "(ILjava/lang/String;)V" );

	if (!desc) desc = "Java-To-COM Error";
	jstring js = env->NewStringUTF(desc);
	jthrowable fail = (jthrowable)env->NewObject( clazz, ctor, hr, js);
	env->DeleteLocalRef(clazz);
	env->Throw(fail);

}

/*
 * Class:     com_argus_activex_ComException
 * Method:    ComException
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V
 */
void ThrowComException( JNIEnv *env, jint hr,
   const wchar_t * desc, const wchar_t * source, const wchar_t * helpFile, jint helpContext )
{
	if (!env) {
		cerr << "ThrowComException: " << hex << hr << ", but JNIEnv is not set..." << endl;
		return;
	}

	if ( env->ExceptionOccurred() ) {
		cerr << "ThrowComException: " << hex << hr << ", but another ExceptionOccurred before..." << endl;
		return;
	}
	//cerr << "ThrowComException: " << hex << hr << endl;
	jclass clazz = env->FindClass("com/argus/activex/ComException");

	// call the constructor that takes hr and message
	jmethodID ctor = GetCTORMethodID( env, clazz, "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V" );

	// wchar_t to char
	jstring jsDesc = NewString(env, desc);
	jstring jsSource = NewString(env, source);
	jstring jsHelpFile = NewString(env, helpFile);

	jthrowable fail = (jthrowable)env->NewObject( clazz, ctor, hr, jsDesc, jsSource, jsHelpFile, helpContext );
	env->DeleteLocalRef(clazz);
	env->Throw(fail);

}

/*
 * Class:     java_lang_Exception
 * Method:    Exception
 * Signature: (Ljava/lang/String;)V
 */
void ThrowDAQException( JNIEnv * env, const char * message ) {

   if (!env || env->ExceptionOccurred() )
      return;

   jclass clazz = env->FindClass("Lcom/argus/daq/DAQException;");
   // call the constructor that takes message
   jmethodID ctor = GetCTORMethodID( env, clazz, "(Ljava/lang/String;)V" );

   jstring js = env->NewStringUTF(message);
   jthrowable fail = (jthrowable)env->NewObject( clazz, ctor, js);
   env->DeleteLocalRef(clazz);
   env->Throw(fail);

}

jmethodID GetCTORMethodID(JNIEnv * env, jclass clazz, const char * sig) {
   jmethodID ctor = env->GetMethodID( clazz, "<init>", sig );
   return ctor;
}

jmethodID GetCTORMethodID(JNIEnv * env, const char * className, const char * sig) {
   jclass clazz = env->FindClass(className);
   jmethodID ctor = GetCTORMethodID(env, clazz, sig);
   env->DeleteLocalRef(clazz);
   return ctor;
}

jmethodID GetMethodID(JNIEnv * env, jclass clazz, const char * name, const char * sig) {
   jmethodID ctor = env->GetMethodID( clazz, name, sig );
   return ctor;
}

jmethodID GetMethodID(JNIEnv * env, const char * className, const char * name, const char * sig) {
   jclass clazz = env->FindClass(className);
   jmethodID ctor = GetMethodID(env, clazz, name, sig);
   env->DeleteLocalRef(clazz);
   return ctor;
}

