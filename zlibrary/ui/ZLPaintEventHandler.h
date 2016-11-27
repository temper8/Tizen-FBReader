/*
 * ZLPaintEventHandler.h
 *
 *  Created on: Nov 27, 2016
 *      Author: Alex
 */

#ifndef ZLPAINTEVENTHANDLER_H_
#define ZLPAINTEVENTHANDLER_H_

#include <efl_extension.h>
class ZLPaintEventHandler {
 public:
	ZLPaintEventHandler(Evas_Object *obj);
	~ZLPaintEventHandler();

	void paint();

	Evas_Object *myEvasObj;

};





#endif /* ZLPAINTEVENT_H_ */
