#pragma once
#include <exception>
#include <jni.h>

class java_exceprion : public std::exception
{

public:

 	void throwJava(JNIEnv*);

protected:

    java_exceprion(const char* message, const char*);
    const char* javaClassException;

};

class compilation_exception : public java_exceprion {

public:

    compilation_exception(const char* message);

};
