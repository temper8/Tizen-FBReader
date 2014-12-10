/*
 * ZLTizenLibraryImplementation.h
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#ifndef ZLTIZENLIBRARYIMPLEMENTATION_H_
#define ZLTIZENLIBRARYIMPLEMENTATION_H_

#include "ZLibraryImplementation.h"

class ZLTizenLibraryImplementation : public ZLibraryImplementation  {
public:
	ZLTizenLibraryImplementation();
	virtual ~ZLTizenLibraryImplementation();

	virtual void initLibrary();

	void init(int &argc, char **&argv);
	ZLPaintContext *createContext();
	void run(ZLApplication *application);

};

#endif /* ZLTIZENLIBRARYIMPLEMENTATION_H_ */
