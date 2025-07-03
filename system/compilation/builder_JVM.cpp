#include "pch.h"
#include "bulder_JVM.h"
#include "cmd.h"

JNIEXPORT jlong JNICALL Java_Builder_setData(JNIEnv* env, jobject, jstring name) {
	std::filesystem::path path = env->GetStringUTFChars(name, nullptr);
	java_project *project = new java_project(path);
	return reinterpret_cast<jlong>(project);
}

JNIEXPORT void JNICALL Java_Builder_deleteData(JNIEnv*, jobject, jlong data) {
	java_project* project = reinterpret_cast<java_project*>(data);
	delete project;
}

JNIEXPORT jstring JNICALL Java_Builder_compilation(JNIEnv* env, jobject, jlong data, jstring mainClass, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path path = env->GetStringUTFChars(mainClass, nullptr);
	java_build build = project->setBuild(path, version);
	std::string error = compilation(build).error;
	return env->NewStringUTF(error.c_str());
}

JNIEXPORT jstring JNICALL Java_Builder_build(JNIEnv* env, jobject, jlong data, jstring mainClass, jstring name, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path path = env->GetStringUTFChars(mainClass, nullptr);
	const char* nameJAR = env->GetStringUTFChars(name, nullptr);
	java_build javaBuild = project->setBuild(path, version);
	std::string error = build(javaBuild, nameJAR).error;
	return env->NewStringUTF(error.c_str());
}

JNIEXPORT jstring JNICALL Java_Builder_run(JNIEnv* env, jobject, jlong data, jstring mainClass, jstring name, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path path = env->GetStringUTFChars(mainClass, nullptr);
	const char* nameJAR = env->GetStringUTFChars(name, nullptr);
	java_build javaBuild = project->setBuild(path, version);
	std::string error = runJar(javaBuild, nameJAR).error;
	return env->NewStringUTF(error.c_str());
}
