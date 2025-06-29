#pragma once
#include <vector>
#include <filesystem>

struct cmd_error
{

	cmd_error(std::string);

	cmd_error();

	std::string error;
	bool is_error;

};


cmd_error ranCmd(std::string);

std::string createClass(std::vector<std::filesystem::path>, std::filesystem::path);

bool createManifest(std::filesystem::path, const char*, double);

std::string createZip(std::filesystem::path);

std::string createJar(std::filesystem::path, const char*);

cmd_error compilation(std::filesystem::path, std::filesystem::path);

cmd_error bild(std::filesystem::path, std::filesystem::path, std::filesystem::path, double, const char*);

cmd_error runJar(std::filesystem::path, std::filesystem::path, std::filesystem::path, double, const char*);

void parcJavaClass(std::filesystem::path, std::vector<std::filesystem::path>*);
