/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_argus_activex_DispatchUtils */

#ifndef _Included_com_argus_activex_DispatchUtils
#define _Included_com_argus_activex_DispatchUtils
#ifdef __cplusplus
extern "C" {
#endif
/* Inaccessible static: DEBUG */
/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    GetJava2COMVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_argus_activex_DispatchUtils_GetJava2COMVersion
  (JNIEnv *, jclass);

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    IsServerRunning
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_argus_activex_DispatchUtils_IsServerRunning
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    GetActiveObject
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_DispatchUtils_GetActiveObject
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    GetHWND
 * Signature: (Ljava/awt/Component;)I
 */
JNIEXPORT jint JNICALL Java_com_argus_activex_DispatchUtils_GetHWND
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_argus_activex_DispatchUtils
 * Method:    ResizeControl
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_com_argus_activex_DispatchUtils_ResizeControl
  (JNIEnv *, jclass, jint, jint, jint);

#ifdef __cplusplus
}
#endif
#endif