/*
 * ZLibraryImplementation.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#include "ZLibraryImplementation.h"


ZLibraryImplementation *ZLibraryImplementation::Instance = 0;

ZLibraryImplementation::ZLibraryImplementation() {
	Instance = this;
}

ZLibraryImplementation::~ZLibraryImplementation() {
	// TODO Auto-generated destructor stub
}

