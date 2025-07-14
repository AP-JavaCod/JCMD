#pragma once
#include "java_project.h"

class cmd_error
{

public:

	cmd_error(std::string);
	
	std::string getMessage();

private:

	std::string message;


};


void ranCmd(std::string, std::filesystem::path);

std::string createClass(java_build);

bool createManifest(java_build, std::filesystem::path);

std::string createZip(std::filesystem::path);

std::string createJar(std::filesystem::path, const char*);

void compilation(java_build);

void build(java_build, const char*);

std::string runJar(java_build, const char*);
