#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>
#include <vector>

class Settings {
// Singlton Stuff Just ignore
public:
	static Settings* Instance();
private:
	Settings() {};
	Settings(Settings const&){};
	static Settings* m_pInstance;

// Class things
public:
	void loadFile(std::string filename);
	int i(std::string key);
	float f(std::string key);
	std::string s(std::string key);
	void setI(std::string key, int i);
	void setF(std::string key, float f);
	void setS(std::string key, std::string s);
private:
	std::map<std::string, int> ints;
	std::map<std::string, float> floats;
	std::map<std::string, std::string> strings;
};

#endif
