#include "pch.h"
#include "bulder_JVM.h"
#include "cmd.h"

JNIEXPORT void JNICALL Java_build_Builder_console(JNIEnv* env, jobject, jstring command) {
	const char* cmd = env->GetStringUTFChars(command, nullptr);
	system(cmd);
}

JNIEXPORT jlong JNICALL Java_build_Builder_setData(JNIEnv* env, jobject, jstring name) {
	std::filesystem::path path = env->GetStringUTFChars(name, nullptr);
	java_project *project = new java_project(path);
	return reinterpret_cast<jlong>(project);
}

JNIEXPORT void JNICALL Java_build_Builder_deleteData(JNIEnv*, jobject, jlong data) {
	java_project* project = reinterpret_cast<java_project*>(data);
	delete project;
}

JNIEXPORT void JNICALL Java_build_Builder_compilation(JNIEnv* env, jobject, jlong data, jstring mainClass, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path path = env->GetStringUTFChars(mainClass, nullptr);
	java_build build = project->setBuild(path, version);
	try {
		compilation(build);
	}
	catch (cmd_error e) {
		env->ThrowNew(env->FindClass("build/JVMException"), e.getMessage().c_str());
	}
}

JNIEXPORT void JNICALL Java_build_Builder_build(JNIEnv* env, jobject, jlong data, jstring mainClass, jstring name, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path path = env->GetStringUTFChars(mainClass, nullptr);
	const char* nameJAR = env->GetStringUTFChars(name, nullptr);
	java_build javaBuild = project->setBuild(path, version);
	build(javaBuild, nameJAR);
}

JNIEXPORT jstring JNICALL Java_build_Builder_run(JNIEnv* env, jobject, jlong data, jstring mainClass, jstring name, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path path = env->GetStringUTFChars(mainClass, nullptr);
	const char* nameJAR = env->GetStringUTFChars(name, nullptr);
	java_build javaBuild = project->setBuild(path, version);
	std::string result = runJar(javaBuild, nameJAR);
	return env->NewStringUTF(result.c_str());
}

JNIEXPORT jint JNICALL Java_build_Builder_sizeClasses(JNIEnv*, jobject, jlong data) {
	java_project* project = reinterpret_cast<java_project*>(data);
	return project->javaClasses.size();
}

JNIEXPORT jstring JNICALL Java_build_Builder_getClassFile(JNIEnv* env, jobject, jlong data, jint index) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::string name = project->javaClasses[index].string();
	return env->NewStringUTF(name.c_str());
}

JNIEXPORT jstring JNICALL Java_build_Builder_getPathClass(JNIEnv* env, jobject, jlong data, jstring file) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path path = env->GetStringUTFChars(file, nullptr);
	std::filesystem::path start = project->nameProject.string() + "\\src";
	std::string name = getFormatPath(path, start);
	return env->NewStringUTF(name.c_str());
}

JNIEXPORT jstring JNICALL Java_build_Builder_getProjectFile(JNIEnv* env, jobject, jlong data) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::string name = project->nameProject.string();
	return env->NewStringUTF(name.c_str());
}
