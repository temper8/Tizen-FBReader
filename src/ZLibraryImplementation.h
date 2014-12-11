/*
 * ZLibraryImplementation.h
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#ifndef ZLIBRARYIMPLEMENTATION_H_
#define ZLIBRARYIMPLEMENTATION_H_

#include "ZLApplication.h"

class ZLibraryImplementation {
	public:
	static ZLibraryImplementation *Instance;

public:
	ZLibraryImplementation();
	virtual ~ZLibraryImplementation();

public:
	virtual void init(int &argc, char **&argv) = 0;
//	virtual ZLPaintContext *createContext() = 0;
	virtual void run(ZLApplication *application) = 0;

	static void initLibrary();
};

#endif /* ZLIBRARYIMPLEMENTATION_H_ */
