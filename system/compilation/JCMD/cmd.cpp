#include "cmd.h"
#include <fstream>
#include <iostream>

cmd_error::cmd_error(std::string error) {
	this->is_error = true;
	this->error = error;
}

cmd_error::cmd_error() {
	is_error = false;
	error = "Not problem";
}

cmd_error ranCmd(std::string cmd) {
	const char* nameFileError = "Log_error.txt";
	std::string c = cmd + " 2> " + nameFileError;
	if (system(c.c_str()) == 0) {
		return cmd_error();
	}
	std::string ms;
	std::string i;
	std::ifstream in(nameFileError);
	if (in.is_open()) {
		while (std::getline(in, i)) {
			ms += i + "\n";
		}
	}
	in.close();
	remove(nameFileError);
	return cmd_error(ms);
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

cmd_error compilation(java_build project) {
	return ranCmd(createClass(project));
}

cmd_error build(java_build projet, const char* nameProject) {
	cmd_error e_cmp = compilation(projet);
	if (e_cmp.is_error) {
		return e_cmp;
	}

	std::filesystem::path dir = projet.build.string() + "\\" + projet.project->nameProject.filename().string();
	std::filesystem::create_directories(dir.string() + "\\META-INF");
	createManifest(projet, dir.string() + "\\META-INF\\MANIFEST.MF");

	cmd_error e_zip = ranCmd(createZip(dir));
	if (e_zip.is_error) {
		return e_zip;
	}

	cmd_error e_jar = ranCmd(createJar(dir, nameProject));
	return e_jar;
}

cmd_error runJar(java_build project, const char* projectNaim) {
	cmd_error e_bild = build(project, projectNaim);
	if (e_bild.is_error) {
		return e_bild;
	}
	return ranCmd("java -jar " + project.build.string() + "\\" + projectNaim);
}
