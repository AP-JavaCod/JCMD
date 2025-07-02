#include "cmd.h"
#include <fstream>
#include <iostream>

cmd_error::cmd_error(std::string error){
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


std::string createClass(java_project project) {
	std::string cmd = "javac -d " + project.nameProject.string() + "\\bild\\" + project.nameProject.filename().string();
	for (const auto& i : project.javaClasses) {
		cmd += " " + i.string();
	}
	return cmd;
}

bool createManifest(java_project project, std::filesystem::path dir) {
	std::ofstream out;
	out.open(dir);
	if (out.is_open()) {
		out << "Manifest-Version: " << project.version << "\n";
		out << "Main-Class: " << getFormatPath(project.mainClass, project.nameProject.string() + "\\src") << "\n\n";
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
	return std::string("rename " + dir.string() + ".zip " + name);
}

cmd_error compilation(java_project project) {
	return ranCmd(createClass(project));
}

cmd_error bild(java_project projet, const char* nameProject) {
	cmd_error e_cmp = compilation(projet);
	if (e_cmp.is_error) {
		return e_cmp;
	}

	std::filesystem::path dir = projet.nameProject.string() + "\\bild\\" + projet.nameProject.filename().string();
	std::filesystem::create_directories(dir.string() + "\\META-INF");
	createManifest(projet, dir.string() + "\\META-INF\\MANIFEST.MF");

	cmd_error e_zip = ranCmd(createZip(dir));
	if (e_zip.is_error) {
		return e_zip;
	}

	cmd_error e_jar = ranCmd(createJar(dir, nameProject));
	return e_jar;
}

cmd_error runJar(java_project project, const char* projectNaim) {
	cmd_error e_bild = bild(project, projectNaim);
	if (e_bild.is_error) {
		return e_bild;
	}
	std::filesystem::path dir = project.nameProject.string() + "\\bild";
	return ranCmd("java -jar " + dir.string() + "\\" + projectNaim);
}
