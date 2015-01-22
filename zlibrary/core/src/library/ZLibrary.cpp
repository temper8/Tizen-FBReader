/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <app.h>

#include "logger.h"


#include <ZLTimeManager.h>
//#include <ZLDialogManager.h>
//#include <ZLImageManager.h>
#include <ZLMessage.h>
#include <ZLUnicodeUtil.h>
#include <ZLLogger.h>

#include "ZLibrary.h"
#include "ZLibraryImplementation.h"

#include "../filesystem/ZLFSManager.h"

#include "../options/ZLConfig.h"

//#include "../../../../FBreader/src/database/booksdb/BooksDB.h"
//#include "../network/ZLNetworkManager.h"

const std::string ZLibrary::FileNameDelimiter("/");
const std::string ZLibrary::PathDelimiter(":");
const std::string ZLibrary::EndOfLine("\n");

void ZLibrary::initLocale() {
	/*
	LocaleManager localeManager;
	localeManager.Construct();

	// Gets the system locale information.
	Locale  systemLocale = localeManager.GetSystemLocale();
	LanguageCode langCode = systemLocale.GetLanguageCode();
	switch (langCode) {
			case LANGUAGE_ENG :
				ourLanguage = "en";
				break;
			case LANGUAGE_FIN :
				ourLanguage = "fi";
				break;
			case LANGUAGE_RUS :
				ourLanguage = "ru";
				break;
	}
	*/
}



bool ZLibrary::ourLocaleIsInitialized = false;
std::string ZLibrary::ourLanguage;
std::string ZLibrary::ourCountry;
std::string ZLibrary::ourZLibraryDirectory;

std::string ZLibrary::ourApplicationName;
std::string ZLibrary::ourImageDirectory;
std::string ZLibrary::ourApplicationImageDirectory;
std::string ZLibrary::ourApplicationDirectory;
std::string ZLibrary::ourApplicationWritableDirectory;
std::string ZLibrary::ourDefaultFilesPathPrefix;

//const std::string ZLibrary::BaseDirectory = std::string(BASEDIR);
//const std::string ZLibrary::BaseDirectory = std::string("/res");
std::string ZLibrary::BaseDirectory;

void ZLibrary::parseArguments(int &argc, char **&argv) {

//	 AppLog("AppRootPath %s", bb);
	 /// путь к ресурсам
	 char *res_path = app_get_shared_resource_path();
		if (res_path) {
			BaseDirectory = std::string(res_path);
			delete res_path;
		}


//	 AppLog( "BaseDirectory %s",ZLibrary::BaseDirectory.c_str());
	static const std::string LANGUAGE_OPTION = "-lang";
	static const std::string LOGGER_OPTION = "-log";
//	AppLog("ZLibrary::parseArguments  while argc=%d ",argc);
	while ((argc > 2) && (argv[1] != 0) && (argv[2] != 0)) {
		const std::string argument = argv[1];
		if (LANGUAGE_OPTION == argument) {
			ourLocaleIsInitialized = true;
			std::string locale = argv[2];
			int index = locale.find('_');
			if (index >= 0) {
				ourLanguage = locale.substr(0, index);
				ourCountry = locale.substr(index + 1);
			} else {
				ourLanguage = locale;
			}
		} else if (LOGGER_OPTION == argument) {
			std::string loggerClasses = argv[2];
			while (size_t index = loggerClasses.find(':') != std::string::npos) {
				ZLLogger::Instance().registerClass(loggerClasses.substr(0, index));
				loggerClasses.erase(0, index + 1);
			}
			ZLLogger::Instance().registerClass(loggerClasses);
		} else {
			ZLLogger::Instance().println(ZLLogger::DEFAULT_CLASS, "unknown argument: " + argument);
		}
		argc -= 2;
		argv += 2;
	};

	//ourZLibraryDirectory = BaseDirectory + FileNameDelimiter + "zlibrary";
	ourZLibraryDirectory = BaseDirectory + "zlibrary";
//	AppLog("ZLibraryDirectory = %s",ourZLibraryDirectory.c_str());

}

void ZLibrary::shutdown() {
//	AppLog("ZLibrary::shutdown()");
//	ZLNetworkManager::deleteInstance();
//	ZLImageManager::deleteInstance();
//	AppLog("ZLImageManager::deleteInstance()");
	ZLCommunicationManager::deleteInstance();
//	ZLDialogManager::deleteInstance();
	ZLFSManager::deleteInstance();

	ZLTimeManager::deleteInstance();
//	ZLConfigManager::deleteInstance();
//	AppLog("ZLConfigManager::deleteInstance()");

//	BooksDB::deleteInstance();
}

std::string ZLibrary::replaceRegExps(const std::string &pattern) {
//ppLog("ZLibrary::replaceRegExps pattern =%s",pattern.c_str());
	static const std::string NAME_PATTERN = "%APPLICATION_NAME%";
	static const std::string LOWERCASENAME_PATTERN = "%application_name%";
	std::string str = pattern;
	int index = -1;
	while ((index = str.find(NAME_PATTERN)) != -1) {
	  str.erase(index, NAME_PATTERN.length());
		str.insert(index, ourApplicationName);
	}
	while ((index = str.find(LOWERCASENAME_PATTERN)) != -1) {
	  str.erase(index, LOWERCASENAME_PATTERN.length());
		str.insert(index, ZLUnicodeUtil::toLower(ourApplicationName));
	}
//	AppLog("ZLibrary::replaceRegExps str =%s",str.c_str());
	return str;
}

#define XMLCONFIGHOMEDIR 1

void ZLibrary::initApplication(const std::string &name) {
	DBG("ZLibrary::initApplication %s",name.c_str() );

	ourApplicationName = name;
	ourImageDirectory = replaceRegExps("/IMAGEDIR");
	//ourApplicationImageDirectory = replaceRegExps("/Res/icons");
	ourApplicationImageDirectory = BaseDirectory + "/icons";
	//ourApplicationDirectory = BaseDirectory + FileNameDelimiter + "FBReader";//ourApplicationName;
	ourApplicationDirectory = BaseDirectory + "FBReader";//ourApplicationName;


	char *data_path = app_get_resource_path();
		if (data_path) {
			ourApplicationWritableDirectory = std::string(data_path);
			delete data_path;
		}


	ourDefaultFilesPathPrefix = ourApplicationDirectory + FileNameDelimiter + "default" + FileNameDelimiter;
	DBG("ZLibrary ourApplicationWritableDirectory =%s",ourApplicationWritableDirectory.c_str());
	DBG("ZLibrary ourApplicationDirectory =%s",ourApplicationDirectory.c_str());
	DBG("ZLibrary ourApplicationImageDirectory =%s",ourApplicationImageDirectory.c_str());
	DBG("ZLibrary ourImageDirectory =%s",ourImageDirectory.c_str());
}

std::string ZLibrary::Language() {
	if (ourLanguage.empty()) {
		if (!ourLocaleIsInitialized) {
			initLocale();
			ourLocaleIsInitialized = true;
		}
	}
//	AppLog("ZLibrary ourLanguage =%s", ourLanguage.c_str());
	if (ourLanguage.empty()) {
		ourLanguage = "en";
	}
	//ourLanguage = "ru";
	return ourLanguage;
}

std::string ZLibrary::Country() {
	if (ourCountry.empty() && !ourLocaleIsInitialized) {
		initLocale();
		ourLocaleIsInitialized = true;
	}
//	AppLog("ZLibrary ourCountry =%s", ourCountry.c_str());
//	ourCountry = "ru";
	return ourCountry;
}



bool ZLibrary::init(int &argc, char **&argv) {

	DBG("ZLib-init");

	ZLibraryImplementation::initLibrary();

	if (ZLibraryImplementation::Instance == 0) {
		return false;
	}

	ZLibraryImplementation::Instance->init(argc, argv);
	DBG("ZLib-init end");
	return true;
}

ZLPaintContext *ZLibrary::createContext() {
	return ZLibraryImplementation::Instance->createContext();
}

void ZLibrary::run(ZLApplication *application) {
	DBG("ZLib-run");
	ZLibraryImplementation::Instance->run(application);
}
