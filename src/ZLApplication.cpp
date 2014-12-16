/*
 * ZLApplication.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#include "logger.h"

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
	DBG("ZLA-createApp");
	//ZLDialogManager::Instance().createApplicationWindow(application);
	//application->initWindow();

	myContext = ZLibrary::createContext();

	return true;
}


void ZLApplication::setView(shared_ptr<ZLView> view) {
	if (view.isNull()) {
		return;
	}

	if (!myViewWidget.isNull()) {
		myViewWidget->setView(view);
		//resetWindowCaption();
		//refreshWindow();
	} else {
		myInitialView = view;
	}
}

void ZLApplication::initWindow() {
	DBG("ZLA-inintWindows");
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

