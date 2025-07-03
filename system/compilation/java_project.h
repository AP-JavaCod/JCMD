#pragma once
#include <vector>
#include <filesystem>
#include <string>

struct java_project
{
	java_project(std::filesystem::path namePriject, std::filesystem::path, double version);
	java_project(std::filesystem::path nameProject, std::filesystem::path, std::filesystem::path, double);

	std::filesystem::path nameProject;
	std::filesystem::path bild;
	std::filesystem::path mainClass;
	std::vector<std::filesystem::path> javaClasses;
	double version;

private:

	void parsJavaClass(std::filesystem::path);

};

std::string getFormatPath(std::filesystem::path, std::filesystem::path);
