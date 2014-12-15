/*
 * ZLApplicationWindow.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#include "ZLApplicationWindow.h"


ZLApplicationWindow *ZLApplicationWindow::ourInstance = 0;

ZLApplicationWindow &ZLApplicationWindow::Instance() {
	return *ourInstance;
}

ZLApplicationWindow::ZLApplicationWindow(ZLApplication *application) : myApplication(application) {
	ourInstance = this;
	myApplication->myWindow = this;
}

void ZLApplicationWindow::init() {
	myApplication->myViewWidget = createViewWidget();

//	initToolbar(WINDOW_TOOLBAR);
//	initToolbar(FULLSCREEN_TOOLBAR);
//	initMenu();
}

void ZLApplicationWindow::refresh() {
//	refreshToolbar(WINDOW_TOOLBAR);
//	refreshToolbar(FULLSCREEN_TOOLBAR);
//	processAllEvents();
}
