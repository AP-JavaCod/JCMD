#pragma once
#include "java_exception.h"
#include "cmd.h"

#ifndef _Included_build_Builder
#define _Included_build_Builder
#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT void JNICALL Java_build_Builder_console(JNIEnv*, jobject, jstring);
	
	JNIEXPORT jlong JNICALL Java_build_Builder_setData(JNIEnv*, jobject, jstring);

	JNIEXPORT void JNICALL Java_build_Builder_deleteData(JNIEnv*, jobject, jlong);

	JNIEXPORT void JNICALL Java_build_Builder_compilation(JNIEnv*, jobject, jlong, jstring, jdouble);

	JNIEXPORT void JNICALL Java_build_Builder_build(JNIEnv*, jobject, jlong, jstring, jstring, jdouble);

	JNIEXPORT jstring JNICALL Java_build_Builder_run(JNIEnv*, jobject, jlong, jstring, jstring, jdouble);

	JNIEXPORT jint JNICALL Java_build_Builder_sizeClasses(JNIEnv*, jobject, jlong);

	JNIEXPORT jstring JNICALL Java_build_Builder_getClassFile(JNIEnv*, jobject, jlong, jint);

	JNIEXPORT jstring JNICALL Java_build_Builder_getPathClass(JNIEnv*, jobject, jlong, jstring);

	JNIEXPORT jstring JNICALL Java_build_Builder_getProjectFile(JNIEnv*, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
