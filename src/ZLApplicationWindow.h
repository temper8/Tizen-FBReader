/*
 * ZLApplicationWindow.h
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#ifndef ZLAPPLICATIONWINDOW_H_
#define ZLAPPLICATIONWINDOW_H_


#include "ZLApplication.h"

class ZLApplicationWindow {
public:
	static ZLApplicationWindow &Instance();

private:
	static ZLApplicationWindow *ourInstance;
	ZLApplication *myApplication;

protected:
	ZLApplicationWindow(ZLApplication *application);

public:
	virtual ~ZLApplicationWindow();

public:
	ZLApplication &application() const;
	void init();
};

#endif /* ZLAPPLICATIONWINDOW_H_ */
