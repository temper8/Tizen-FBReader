/*
 * ZLTizenApplicationWindow.h
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#ifndef ZLTIZENAPPLICATIONWINDOW_H_
#define ZLTIZENAPPLICATIONWINDOW_H_

#include <string>
#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "tizen-fbreader"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.tizen-fbreader"
#endif

#include "ZLApplicationWindow.h"

class ZLTizenApplicationWindow : public ZLApplicationWindow {
public:
	ZLTizenApplicationWindow(ZLApplication *application);
	virtual ~ZLTizenApplicationWindow();

	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;

	static void win_back_cb(void *data, Evas_Object *obj, void *event_info);

protected:
	virtual ZLViewWidget *createViewWidget();

};

#endif /* ZLTIZENAPPLICATIONWINDOW_H_ */
