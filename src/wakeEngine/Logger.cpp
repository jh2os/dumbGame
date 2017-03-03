#include <stddef.h>
#include "Logger.h"

// Global static pointer used to ensure a single instance of the class.
Logger* Logger::m_pInstance = NULL;

Logger* Logger::Instance() {
	if(!m_pInstance)
		m_pInstance = new Logger;

	return m_pInstance;
}

bool Logger::setLogFile(std::string logFileStr) {
	logFile = logFileStr;
	if (outfile.is_open())
		outfile.close();
	outfile.open(logFile);
	//state = LOGGER_OFF;
	return true;
}

void Logger::endline() {
	outfile << "\r\n";
}

bool Logger::closeLogFile() {
	outfile.close();
	return true;
}
