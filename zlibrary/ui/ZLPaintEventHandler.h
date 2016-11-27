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
	ZLPaintEventHandler(Evas_Object *image);
	~ZLPaintEventHandler();

	void paint();

	Evas_Object *myImage;

};





#endif /* ZLPAINTEVENT_H_ */
