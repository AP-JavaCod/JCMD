#pragma once
#include <vector>
#include <filesystem>
#include <string>

struct java_project;

struct java_build {

	java_build(java_project*, std::filesystem::path, std::filesystem::path, double);

	java_project* project;
	std::filesystem::path build;
	std::filesystem::path mainClass;
	double version;

};

struct java_project
{
	java_project(std::filesystem::path);

	std::filesystem::path nameProject;
	std::vector<std::filesystem::path> javaClasses;

	java_build setBuild(std::filesystem::path, std::filesystem::path, double version);

private:

	void parsJavaClass(std::filesystem::path);

};

std::string getFormatPath(std::filesystem::path, std::filesystem::path);
