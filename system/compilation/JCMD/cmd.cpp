#include "pch.h"
#include "cmd.h"
#include <fstream>
#include <iostream>

void ranCmd(std::string cmd, std::filesystem::path dir) {
	std::string nameFileError = dir.string() + "Log_error.txt";
	std::string c = cmd + " 2> " + nameFileError;
	if (system(c.c_str()) != 0) {
		std::string ms;
		std::string i;
		std::ifstream in(nameFileError);
		if (in.is_open()) {
			while (std::getline(in, i)) {
				ms += i + "\n";
			}
		}
		in.close();
		remove(nameFileError.c_str());
		throw compilation_exception(ms.c_str());
	}
}


std::string createClass(java_build javaBuild) {
	java_project javaProject = *javaBuild.project;
	std::filesystem::path dir = javaBuild.build.string() + "\\" + javaProject.nameProject.filename().string();
	std::filesystem::remove_all(dir);
	std::string cmd = "javac -d " + dir.string();
	for (const auto& i : javaProject.javaClasses) {
		cmd += " " + i.string();
	}
	return cmd;
}

bool createManifest(java_build javaBuild, std::filesystem::path dir) {
	java_project javaProject = *javaBuild.project;
	std::ofstream out;
	out.open(dir);
	if (out.is_open()) {
		out << "Manifest-Version: " << javaBuild.version << "\n";
		out << "Main-Class: " << getFormatPath(javaBuild.mainClass, javaProject.nameProject.string() + "\\src") << "\n\n";
		out.close();
		return true;
	}
	out.close();
	return false;
}

std::string createZip(std::filesystem::path dir) {
	std::string cmd = "cd " + dir.string() + " && tar -a -c -f " + dir.string() + ".zip";
	for (const auto& i : std::filesystem::directory_iterator(dir)) {
		cmd += " " + i.path().filename().string();
	}
	return cmd;
}

std::string createJar(std::filesystem::path dir, const char* name) {
	std::string fil = dir.parent_path().string() + "\\" + name;
	remove(fil.c_str());
	return std::string("rename " + dir.string() + ".zip " + name);
}

void compilation(java_build project) {
	ranCmd(createClass(project), project.build);
}

void build(java_build projet, const char* nameProject) {
	std::filesystem::path dir = projet.build.string() + "\\" + projet.project->nameProject.filename().string();
	std::filesystem::create_directories(dir.string() + "\\META-INF");
	createManifest(projet, dir.string() + "\\META-INF\\MANIFEST.MF");
	system(createZip(dir).c_str());
	system(createJar(dir, nameProject).c_str());
}

std::string runJar(java_build project, const char* projectNaim) {
	std::string file = project.build.string() + "\\result_data.txt";
	std::string runCod = "java -jar " + project.build.string() + "\\" + projectNaim + " >> " + file;
	ranCmd(runCod, file);
	std::string ms;
	std::string i;
	std::ifstream in(file);
	if (in.is_open()) {
		while (std::getline(in, i)) {
			ms += i + "\n";
		}
	}
	in.close();
	remove(file.c_str());
	return ms;
	
}
