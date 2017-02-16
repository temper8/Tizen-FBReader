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
#define PACKAGE "org.tizen.fbreader"
#endif

class ZLTizenLibraryImplementation : public ZLibraryImplementation  {
public:
	ZLTizenLibraryImplementation();
	virtual ~ZLTizenLibraryImplementation();



	void init(int &argc, char **&argv);
	ZLPaintContext *createContext();
	void run(ZLApplication *application);

	//static ZLTizenApplicationWindow *myWindow;

};

#endif /* ZLTIZENLIBRARYIMPLEMENTATION_H_ */
