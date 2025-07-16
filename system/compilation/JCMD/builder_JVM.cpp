#include "pch.h"
#include "bulder_JVM.h"

JNIEXPORT void JNICALL Java_build_JavaProjectBuilder_console(JNIEnv* env, jobject, jstring command) {
	const char* cmd = env->GetStringUTFChars(command, nullptr);
	system(cmd);
}

JNIEXPORT jlong JNICALL Java_build_JavaProjectBuilder_setData(JNIEnv* env, jobject, jstring name) {
	std::filesystem::path path = env->GetStringUTFChars(name, nullptr);
	java_project *project = new java_project(path);
	return reinterpret_cast<jlong>(project);
}

JNIEXPORT void JNICALL Java_build_JavaProjectBuilder_deleteData(JNIEnv*, jobject, jlong data) {
	java_project* project = reinterpret_cast<java_project*>(data);
	delete project;
}

JNIEXPORT void JNICALL Java_build_JavaProjectBuilder_compilation(JNIEnv* env, jobject, jlong data, jstring buildDir, jstring mainClass, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path pathBuild = env->GetStringUTFChars(buildDir, nullptr);
	std::filesystem::path pathMainClass = env->GetStringUTFChars(mainClass, nullptr);
	java_build build = project->setBuild(pathBuild ,pathMainClass, version);
	try {
		compilation(build);
	}
	catch (compilation_exception & ex) {
		ex.throwJava(env);
	}
}

JNIEXPORT void JNICALL Java_build_JavaProjectBuilder_build(JNIEnv* env, jobject, jlong data, jstring buildDir, jstring mainClass, jstring name, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path pathBuild = env->GetStringUTFChars(buildDir, nullptr);
	std::filesystem::path pathMainClass = env->GetStringUTFChars(mainClass, nullptr);
	const char* nameJAR = env->GetStringUTFChars(name, nullptr);
	java_build javaBuild = project->setBuild(pathBuild, pathMainClass, version);
	build(javaBuild, nameJAR);
}

JNIEXPORT jstring JNICALL Java_build_JavaProjectBuilder_run(JNIEnv* env, jobject, jlong data, jstring buildDir, jstring mainClass, jstring name, jdouble version) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path pathBuild = env->GetStringUTFChars(buildDir, nullptr);
	std::filesystem::path pathMainClass = env->GetStringUTFChars(mainClass, nullptr);
	const char* nameJAR = env->GetStringUTFChars(name, nullptr);
	java_build javaBuild = project->setBuild(pathBuild, pathMainClass, version);
	std::string result = runJar(javaBuild, nameJAR);
	return env->NewStringUTF(result.c_str());
}

JNIEXPORT jint JNICALL Java_build_JavaProjectBuilder_sizeClasses(JNIEnv*, jobject, jlong data) {
	java_project* project = reinterpret_cast<java_project*>(data);
	return project->javaClasses.size();
}

JNIEXPORT jstring JNICALL Java_build_JavaProjectBuilder_getClassFile(JNIEnv* env, jobject, jlong data, jint index) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::string name = project->javaClasses[index].string();
	return env->NewStringUTF(name.c_str());
}

JNIEXPORT jstring JNICALL Java_build_JavaProjectBuilder_getPathClass(JNIEnv* env, jobject, jlong data, jstring file) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::filesystem::path path = env->GetStringUTFChars(file, nullptr);
	std::filesystem::path start = project->nameProject.string() + "\\src";
	std::string name = getFormatPath(path, start);
	return env->NewStringUTF(name.c_str());
}

JNIEXPORT jstring JNICALL Java_build_JavaProjectBuilder_getProjectFile(JNIEnv* env, jobject, jlong data) {
	java_project* project = reinterpret_cast<java_project*>(data);
	std::string name = project->nameProject.string();
	return env->NewStringUTF(name.c_str());
}
