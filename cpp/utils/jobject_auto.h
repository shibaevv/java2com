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

#ifndef jobject_autoH
#define jobject_autoH

#include <jni.h>

//---------------------------------------------------------------------------
namespace argus {

class jobject_auto
{
private:
   JNIEnv * m_env;
   jobject m_jobject;

   void init(jclass clazz);

public:
	jobject_auto( JNIEnv * env, const char * className );
	jobject_auto( JNIEnv * env, jclass clazz );

	~jobject_auto();

	operator jobject () const { return m_jobject; }

};

}

#endif
