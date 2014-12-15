/*
 * ZLApplication.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#include "ZLApplication.h"
#include "ZLibrary.h"
#include "ZLApplicationWindow.h"
#include "ZLViewWidget.h"

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

shared_ptr<ZLPaintContext> ZLApplication::context() {
	return myContext;
}


bool ZLApplication::createApplication(){
	//ZLDialogManager::Instance().createApplicationWindow(application);
	//application->initWindow();

	myContext = ZLibrary::createContext();

	return true;
}

void ZLApplication::initWindow() {
//	if (KeyboardControlOption.value()) {
//		grabAllKeys(true);
//	}
//	myWindow->init();
//	setView(myInitialView);
}

void ZLApplication::refreshWindow() {
	if (!myViewWidget.isNull()) {
		myViewWidget->repaint();
	}
	if (!myWindow.isNull()) {
		myWindow->refresh();
	}
}

