#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <time.h>



class Logger {
public:
	static Logger* Instance();
	bool dbg;
	std::string logFile;
	void debug(bool option) {dbg = option;}
	bool setLogFile(std::string logFile);
	template<typename A> 
	void write(A s) { this->outfile << s;	};

	// This is dirty
	template<typename A>
	void writeLine(A a) {
		writeLine(a,"","","","","","","","","");
	}
	template<typename A, typename B>
	void writeLine(A a, B b) {
		writeLine(a,b,"","","","","","","","");
	}
	template<typename A, typename B, typename C>
	void writeLine(A a, B b, C c) {
		writeLine(a,b,c,"","","","","","","");
	}
	template<typename A, typename B, typename C, typename D>
	void writeLine(A a, B b, C c, D d) {
		writeLine(a,b,c,d,"","","","","","");	
	}
	template<typename A, typename B, typename C, typename D, typename E>
	void writeLine(A a, B b, C c, D d, E e) {
		writeLine(a,b,c,d,e,"","","","","");	
	}
	template<typename A, typename B, typename C, typename D, typename E, typename F>
	void writeLine(A a, B b, C c, D d, E e, F f) {
		writeLine(a,b,c,d,e,f,"","","","");
	}
	template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>
	void writeLine(A a, B b, C c, D d, E e, F f, G g) {
		writeLine(a,b,c,d,e,f,g,"","","");
	}
	template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
	void writeLine(A a, B b, C c, D d, E e, F f, G g, H h) {
		writeLine(a,b,c,d,e,f,g,h,"","");
	}
	template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
	void writeLine(A a, B b, C c, D d, E e, F f, G g, H h, I i) {
		writeLine(a,b,c,d,e,f,g,h,i,"");
	}
	template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J>
	void writeLine(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j) {
		this->outfile << a << b << c << d << e << f << g << h << i << j << "\r\n";
	}	
	// Sorry
	

	
	void endline();
	bool closeLogFile(); 
private:
//	time_t timer;
	std::ofstream outfile;
	Logger(){this->setLogFile("Engine.log");}
	Logger(Logger const&) { this->setLogFile("Engine.log"); }
//	Logger& operator=(Logger const&){};
	static Logger* m_pInstance;
};

#endif
