#pragma once
#include "java_project.h"

struct cmd_error
{

	cmd_error(std::string);

	cmd_error();

	std::string error;
	bool is_error;

};


cmd_error ranCmd(std::string);

std::string createClass(java_build);

bool createManifest(java_build, std::filesystem::path);

std::string createZip(std::filesystem::path);

std::string createJar(std::filesystem::path, const char*);

cmd_error compilation(java_build);

cmd_error build(java_build, const char*);

cmd_error runJar(java_build, const char*);
