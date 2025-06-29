#include "cmd.h"
#include <string>
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


std::string createClass(std::vector<std::filesystem::path> javaClass, std::filesystem::path path) {
	std::string cmd = "javac -d " + path.string();
	for (const auto& i : javaClass) {
		cmd += " " + i.string();
	}
	return cmd;
}

bool createManifest(std::filesystem::path der, const char* mainClass, double version) {
	std::ofstream out;
	out.open(der);
	if (out.is_open()) {
		out << "Manifest-Version: " << version << "\n";
		out << "Main-Class: " << mainClass << "\n\n";
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

cmd_error compilation(std::filesystem::path project, std::filesystem::path dir) {
	std::vector <std::filesystem::path> data;
	parcJavaClass(project.string() + "\\src", &data);
	return ranCmd(createClass(data, dir));
}

cmd_error bild(std::filesystem::path project, std::filesystem::path dir, std::filesystem::path mainFile, double version, const char* nameProject) {
	cmd_error e_cmp = compilation(project, dir);
	if (e_cmp.is_error) {
		return e_cmp;
	}

	std::filesystem::create_directories(dir.string() + "\\META-INF");
	std::string mainName = mainFile.filename().string();
	mainName.resize(mainName.size() - 5, ' ');
	for (std::filesystem::path i = mainFile.parent_path(); i.filename() != "src"; i = i.parent_path()) {
		mainName = i.filename().string() + "." + mainName;
	}
	createManifest(dir.string() + "\\META-INF\\MANIFEST.MF", mainName.c_str(), version);

	cmd_error e_zip = ranCmd(createZip(dir));
	if (e_zip.is_error) {
		return e_zip;
	}

	cmd_error e_jar = ranCmd(createJar(dir, nameProject));
	return e_jar;
}

cmd_error runJar(std::filesystem::path project, std::filesystem::path dir, std::filesystem::path mainFile, double version, const char* projectNaim) {
	cmd_error e_bild = bild(project, dir, mainFile, version, projectNaim);
	if (e_bild.is_error) {
		return e_bild;
	}
	return ranCmd(std::string("java -jar " + dir.parent_path().string() + "\\" + projectNaim));
}

void parcJavaClass(std::filesystem::path der, std::vector<std::filesystem::path>* data) {
	for (const auto &i : std::filesystem::directory_iterator(der)) {
		std::filesystem::path fil = i.path();
		if (std::filesystem::is_directory(fil)) {
			parcJavaClass(fil, data);
		}
		else if(fil.extension() == ".java")
		{
			data->push_back(fil);
		}
	}
}
