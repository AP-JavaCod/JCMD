#pragma once
#include "java_exception.h"
#include "cmd.h"

#ifndef _Included_build_JavaProjectBuilder
#define _Included_build_JavaProjectBuilder
#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT void JNICALL Java_build_JavaProjectBuilder_console(JNIEnv*, jobject, jstring);
	
	JNIEXPORT jlong JNICALL Java_build_JavaProjectBuilder_setData(JNIEnv*, jobject, jstring);

	JNIEXPORT void JNICALL Java_build_JavaProjectBuilder_deleteData(JNIEnv*, jobject, jlong);

	JNIEXPORT void JNICALL Java_build_JavaProjectBuilder_compilation(JNIEnv*, jobject, jlong, jstring, jstring, jdouble);

	JNIEXPORT void JNICALL Java_build_JavaProjectBuilder_build(JNIEnv*, jobject, jlong, jstring, jstring, jstring, jdouble);

	JNIEXPORT jstring JNICALL Java_build_JavaProjectBuilder_run(JNIEnv*, jobject, jlong, jstring, jstring, jstring, jdouble);

	JNIEXPORT jint JNICALL Java_build_JavaProjectBuilder_sizeClasses(JNIEnv*, jobject, jlong);

	JNIEXPORT jstring JNICALL Java_build_JavaProjectBuilder_getClassFile(JNIEnv*, jobject, jlong, jint);

	JNIEXPORT jstring JNICALL Java_build_JavaProjectBuilder_getPathClass(JNIEnv*, jobject, jlong, jstring);

	JNIEXPORT jstring JNICALL Java_build_JavaProjectBuilder_getProjectFile(JNIEnv*, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
