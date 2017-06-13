#include <stddef.h>
#include <fstream>
#include <sstream>
#include "Logger.h"
#include "Settings.h"
#include <iostream>

Settings* Settings::m_pInstance = NULL;

Settings* Settings::Instance() {
	if(!m_pInstance)
		m_pInstance = new Settings;
	return m_pInstance;
}

void Settings::loadFile(std::string filename) {
	Logger* log = Logger::Instance();
	std::string line;
	std::ifstream settingsFile(filename.c_str());

	if(settingsFile.is_open()) {

		int counter = 1;
		std::string key;
		int i;
		float f;
		std::string s;

		log->writeLine("Reading in settings file: ", filename);
		while(std::getline(settingsFile, line)) {
			if(!line.empty()) {
				std::istringstream iss(line);
				std::string type;
				iss >> type;
				if ( type == "i") {
					iss >> key >> i;

					this->setI(key, i);
				}
				else if ( type == "f") {
					iss >> key >> f;
					this->setF(key, f);
				}
				else if (type == "s") {
					iss >> key;
					getline(iss, s);
					int start = s.find_first_not_of(' ');
					int len = s.length();
					this->setS(key, s.substr(start, len));
				}
				else if (type == "#") {}
				else {
					log->writeLine("Error in reading line ", counter, " in settings file: ", filename);
					log->writeLine("Please use a valid type identifier (i,f,s)");
				}
			}
			counter++;
		}

	} else {
		log->writeLine("Failed to open settings file: ",filename);
		log->writeLine("Shutting down program");
		log->closeLogFile();
		//exit(-1);
		//return -1
	}
}

int Settings::i(std::string key) {
	return this->ints[key];
}

float Settings::f(std::string key) {
	return this->floats[key];
}

std::string Settings::s(std::string key) {
	return this->strings[key];
}

void Settings::setI(std::string key, int i) {
	this->ints[key] = i;
}

void Settings::setF(std::string key, float f) {
	this->floats[key] = f;
}

void Settings::setS(std::string key, std::string s) {
	this->strings[key] = s;
}
