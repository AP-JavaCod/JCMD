#pragma once
#include "java_project.h"
#include "java_exception.h"

void ranCmd(std::string, std::filesystem::path);

std::string createClass(java_build);

bool createManifest(java_build, std::filesystem::path);

std::string createZip(std::filesystem::path);

std::string createJar(std::filesystem::path, const char*);

void compilation(java_build);

void build(java_build, const char*);

std::string runJar(java_build, const char*);
