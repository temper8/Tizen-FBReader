/*
 * PaintEventHandler.h
 *
 *  Created on: Nov 27, 2016
 *      Author: Alex
 */

#ifndef PAINTEVENTHANDLER_H_
#define PAINTEVENTHANDLER_H_

#include <efl_extension.h>
#include <functional>

class PaintEventHandler {
 public:
	PaintEventHandler(Evas_Object *obj);
	~PaintEventHandler();

	void paint();
	std::function<void(int)> f_display;
	static void print_num(int i);
	Evas_Object *myEvasObj;

};





#endif /* ZLPAINTEVENT_H_ */
