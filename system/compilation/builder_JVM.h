#include <jni.h>

#ifndef _Included_Builder
#define _Included_Builder
#ifdef __cplusplus
extern "C" {
#endif
	
	JNIEXPORT jlong JNICALL Java_Builder_setData(JNIEnv*, jobject, jstring);

	JNIEXPORT void JNICALL Java_Builder_deleteData(JNIEnv*, jobject, jlong);

	JNIEXPORT jstring JNICALL Java_Builder_compilation(JNIEnv*, jobject, jlong, jstring, jdouble);

	JNIEXPORT jstring JNICALL Java_Builder_build(JNIEnv*, jobject, jlong, jstring, jstring, jdouble);

	JNIEXPORT jstring JNICALL Java_Builder_run(JNIEnv*, jobject, jlong, jstring, jstring, jdouble);

	JNIEXPORT jint JNICALL Java_Builder_sizeClasses(JNIEnv*, jobject, jlong);

	JNIEXPORT jstring JNICALL Java_Builder_getClassFile(JNIEnv*, jobject, jlong, jint);

	JNIEXPORT jstring JNICALL Java_Builder_getClassFormat(JNIEnv*, jobject, jlong, jint);

	JNIEXPORT jstring JNICALL Java_Builder_getProjectFile(JNIEnv*, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
