#include "java_project.h"

java_project::java_project(std::filesystem::path nameProject, std::filesystem::path mainClass, double version) {
	this->nameProject = nameProject;
	this->bild = nameProject.string() + "\\bild";
	this->mainClass = mainClass;
	this->version = version;
	parsJavaClass(nameProject);
}

java_project::java_project(std::filesystem::path nameProject, std::filesystem::path bild, std::filesystem::path mainClass, double version) {
	this->nameProject = nameProject;
	this->bild = bild;
	this->mainClass = mainClass;
	this->version = version;
	parsJavaClass(nameProject);
}

void java_project::parsJavaClass(std::filesystem::path path) {
	for (const auto& i : std::filesystem::directory_iterator(path)) {
		std::filesystem::path fil = i.path();
		if (std::filesystem::is_directory(fil)) {
			parsJavaClass(fil);
		}
		else if (fil.extension() == ".java")
		{
			javaClasses.push_back(fil);
		}
	}
}

std::string getFormatPath(std::filesystem::path path, std::filesystem::path start) {
	std::filesystem::path fil = std::filesystem::relative(path, start);
	std::string name = fil.filename().string();
	int sizeFormat = path.extension().string().size();
	name.resize(name.size() - sizeFormat, ' ');
	while ((fil = fil.parent_path()) != "") {
		name = fil.filename().string() + "." + name;
	}
	return name;
}
