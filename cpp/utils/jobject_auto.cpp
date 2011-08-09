//---------------------------------------------------------------------------
#include "jobject_auto.h"

#include <iostream>

using namespace argus;

//---------------------------------------------------------------------------
jobject_auto::jobject_auto( JNIEnv *env, const char * className )
    : m_env(env), m_jobject(0)
{
   jclass clazz = m_env->FindClass( className );
   init(clazz);
   m_env->DeleteLocalRef(clazz);
}

jobject_auto::jobject_auto( JNIEnv *env, jclass clazz )
    : m_env(env), m_jobject(0)
{
   init(clazz );
}

void jobject_auto::init(jclass clazz ) {
   // default ctor has to be defined
   jmethodID ctor = m_env->GetMethodID( clazz, "<init>", "()V" );
   m_jobject = m_env->NewObject( clazz, ctor );
   if (!m_jobject) {
      std::cout << "No m_jobject: " << m_jobject << ", clazz: " << clazz << ", ctor: " << ctor << std::endl;
   }
}

jobject_auto::~jobject_auto() {
   if (m_jobject) {
      m_env->DeleteLocalRef(m_jobject);
      m_jobject = 0;
   }
   m_env = 0;
}

