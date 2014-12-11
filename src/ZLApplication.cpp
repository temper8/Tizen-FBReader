/*
 * ZLApplication.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#include "ZLApplication.h"

ZLApplicationBase::ZLApplicationBase(const std::string &name) {
	// TODO Auto-generated constructor stub

}

ZLApplicationBase::~ZLApplicationBase() {
	// TODO Auto-generated destructor stub
}

ZLApplication *ZLApplication::ourInstance = 0;

ZLApplication &ZLApplication::Instance() {
	return *ourInstance;
}

void ZLApplication::deleteInstance() {
	if (ourInstance != 0) {
		delete ourInstance;
		ourInstance = 0;
	}
}

ZLApplication::ZLApplication(const std::string &name) : ZLApplicationBase(name)
 {
	ourInstance = this;
//	myContext = ZLibrary::createContext();

}

ZLApplication::~ZLApplication() {
	ourInstance = 0;
}

bool ZLApplication::createApplication(){
	//ZLDialogManager::Instance().createApplicationWindow(application);
	//application->initWindow();
	return true;
}
