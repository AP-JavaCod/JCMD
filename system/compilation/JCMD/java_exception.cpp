#include "pch.h"
#include "java_exception.h"

java_exception::java_exception(const char* message, const char* javaClass) : std::exception(message) {
	javaClassException = javaClass;
}

void java_exception::throwJava(JNIEnv *env) {
	jclass javaClass = env->FindClass(javaClassException);
	env->ThrowNew(javaClass, what());
}

compilation_exception::compilation_exception(const char* message) : java_exceprton(message, "build/JVMException") {

}
