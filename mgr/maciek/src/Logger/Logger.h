//
// C++ Interface: logger
//
// Description:
// Author: M.Gabka <mgabka@gmail.com>, (C) 2009
// Copyright: See COPYING file that comes with this distribution


#ifndef LOGGER_H_
#define LOGGER_H_

enum level {INFO, DBG, SYSERR, FATAL_ERR, WARNING,PATH};

#include <log4cxx/logger.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/simplelayout.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/logmanager.h>

#include <assert.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include<cstdio>
#include<stdarg.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


using namespace std;

/**
 * Class for logging system
 * First Log should be done after loading coonfiguration files,
 * so after calling Config::getInstance().load(), because before that
 * localisations of logging files are unknown.
 * Even default value comes from Config object.
 */
class Logger{
public:
	static Logger& getInstance(){
			static Logger logger_;
			return logger_;
		}
	/// tworzy katalog jesli nie istnieje
	short static create_dir_if_doesnt_exist(string dir);
private:
	///file name where logs are saved
	string logFile;
	///file name where robots path are saved
	string robotsPath;
	Logger();
	Logger(Logger& logger);
	/* @brief get from file path to file
	 * otrzymujemy z pliku sciezke do pliku
	 *
	 */
	static int nrChangesPathFile;
	string det_dir_from_filename(string file_name);
	/// sprawdza czy katalogi i pliki z logami istnieja,w p.p  tworzy je
	bool init_log_dir_and_files();
	/*@brief tworzy plik jesli nie istnieje
	 *
	 * @return true jesli operacja sie udala
	 */
	bool createFileIfNotExist(string filename);

public:
	/** @brief wlacza wypisywanie wszystkich  logow na konsole
	 *
	 * @return true jesli operacja zakonczona pomyslnie
	 */
	bool enableCout();
	/** @brief wylacza wypisywanie wszystkich  logow na konsole
	 *
	 * @return true jesli operacja zakonczona pomyslnie
	 */
	bool disableCout();
	/**
	 * @brief tworzy obiekty odpowiadajace za logowanie do poszczegolnych plikow
	 * @return true  jesli operacja wykonana poprawnie
	 */
	bool createLoggers();
//	void changeLogPathFile(std::string fileName);
	/**
	 * @brief loguje do pliku zadana wiadomosc
	 * @param dane wiadomosc do zapisania
	 * @param level_ poziom istotnosci wiadomosci
	 * @param logger_ gdzie logujemy wiadomosc
	 */
	void LogToFile(enum level level_, const char *data,...);
	void LogToFile(enum level level_,  std::ostringstream & ois);

	virtual ~Logger();

};
#endif //LOGGER_H_
