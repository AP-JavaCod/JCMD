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

std::string createClass(java_project);

bool createManifest(java_project, std::filesystem::path);

std::string createZip(std::filesystem::path);

std::string createJar(std::filesystem::path, const char*);

cmd_error compilation(java_project);

cmd_error bild(java_project, const char*);

cmd_error runJar(java_project, const char*);
