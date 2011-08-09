//---------------------------------------------------------------------------
#include "jobjectArray_auto.h"

using namespace argus;

//---------------------------------------------------------------------------
jobjectArray_auto::jobjectArray_auto( JNIEnv * env, unsigned int len, const char * className, jobject initObject )
    : env(0), clazz(0), clazzDeleteLocalRef(true), m_jobjectArray(0)
{
   init( env, len, env->FindClass( className ), initObject );
}

jobjectArray_auto::jobjectArray_auto( JNIEnv * env, unsigned int len, jclass clazz, jobject initObject )
    : env(0), clazz(0), clazzDeleteLocalRef(false), m_jobjectArray(0)
{
   init( env, len, clazz, initObject );
}

jobjectArray_auto::~jobjectArray_auto() {
   if (clazz && clazzDeleteLocalRef)
      env->DeleteLocalRef(clazz);
   if (m_jobjectArray)
      env->DeleteLocalRef(m_jobjectArray);
}

void jobjectArray_auto::init( JNIEnv * env, unsigned int len, jclass clazz, jobject initObject ) {
   this->env = env;
   this->len = len;
   this->clazz = clazz;
   this->m_jobjectArray = env->NewObjectArray( len, clazz, initObject );
}

jobject jobjectArray_auto::NewObject() const
{
   // default ctor has to be defined
   jmethodID ctor = env->GetMethodID( clazz, "<init>", "()V" );
   return env->NewObject( clazz, ctor );
}

