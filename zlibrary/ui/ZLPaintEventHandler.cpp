/*
 * ZLPaintEventHandler.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: Alex
 */

#include "ZLPaintEventHandler.h"
#include "ZLTizenCairo.h"

#include "logger.h"

static void evas_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ZLPaintEventHandler *pe = (ZLPaintEventHandler*)data;
	pe->paint();
}

ZLPaintEventHandler::ZLPaintEventHandler(Evas_Object *obj): myEvasObj(obj){


	evas_object_event_callback_add(obj, EVAS_CALLBACK_RESIZE, evas_resize_cb, this);
}

void ZLPaintEventHandler::paint(){
	DBG("ZLPaintEventHandler::paint");
	ZLTizenCairo *myCairo = new ZLTizenCairo(myEvasObj);
	myCairo->clear(ZLColor(255, 0, 0));
	myCairo->flush_cairo();
}
