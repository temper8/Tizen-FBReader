/*
 * PaintEventHandler.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: Alex
 */

#include "PaintEventHandler.h"
#include "ZLTizenCairo.h"

#include "logger.h"




static void evas_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	PaintEventHandler *pe = (PaintEventHandler*)data;
	pe->paint();
}

PaintEventHandler::PaintEventHandler(Evas_Object *obj): myEvasObj(obj){


	evas_object_event_callback_add(obj, EVAS_CALLBACK_RESIZE, evas_resize_cb, this);
}
void PaintEventHandler::print_num(int i)
{
	DBG("print_num %d",i);
}

void PaintEventHandler::paint(){
	DBG("ZLPaintEventHandler::paint");
	ZLTizenCairo *myCairo = new ZLTizenCairo(myEvasObj);
	myCairo->clear(ZLColor(255, 0, 0));
	myCairo->flush_cairo();

    // store a free function
    f_display = print_num;
    f_display(-9);

}
