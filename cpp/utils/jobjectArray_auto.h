////////////////////////////////////////////////////////////////////////////////
// Company:    Argus Software                                                 //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    wrapper class												               //
//			      handle jobject creation            						            //
////////////////////////////////////////////////////////////////////////////////
//
// jobject_auto.h: interface for the jobject_auto class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef jobjectArray_autoH
#define jobjectArray_autoH

#include <jni.h>

//---------------------------------------------------------------------------
namespace argus {

class jobjectArray_auto
{
private:
   JNIEnv * env;

   unsigned int len;

   jclass clazz;
   bool clazzDeleteLocalRef;

   jobjectArray m_jobjectArray;

   void init( JNIEnv * env, unsigned int len, jclass clazz, jobject init = NULL );

public:
	jobjectArray_auto( JNIEnv * env, unsigned int len, const char * className, jobject initObject = NULL );
	jobjectArray_auto( JNIEnv * env, unsigned int len, jclass clazz, jobject initObject = NULL );

	~jobjectArray_auto();

	operator jobjectArray () const { return m_jobjectArray; }

	jobject NewObject() const;

};

}

#endif  // jobjectArray_autoH
