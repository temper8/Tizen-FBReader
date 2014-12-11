/*
 * ZLTizenLibraryImplementation.h
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#ifndef ZLTIZENLIBRARYIMPLEMENTATION_H_
#define ZLTIZENLIBRARYIMPLEMENTATION_H_

#include "ZLibraryImplementation.h"
#include "ZLTizenApplicationWindow.h"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.tizen-fbreader"
#endif

class ZLTizenLibraryImplementation : public ZLibraryImplementation  {
public:
	ZLTizenLibraryImplementation();
	virtual ~ZLTizenLibraryImplementation();



	void init(int &argc, char **&argv);
//	ZLPaintContext *createContext();
	void run(ZLApplication *application);

	static bool	app_create(void *data);
	static void	app_control(app_control_h app_control, void *data);
	static void app_pause(void *data);
	static void app_resume(void *data);
	static void app_terminate(void *data);

	static ZLTizenApplicationWindow *myWindow;
};

#endif /* ZLTIZENLIBRARYIMPLEMENTATION_H_ */
