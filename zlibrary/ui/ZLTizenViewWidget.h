/*
 * ZLTizenViewWidget.h
 *
 *  Created on: Dec 12, 2014
 *      Author: Alex
 */

#ifndef ZLTIZENVIEWWIDGET_H_
#define ZLTIZENVIEWWIDGET_H_

#include "ZLViewWidget.h"
#include "ZLView.h"
#include <efl_extension.h>
#include "ZLTizenPaintContext.h"

class ZLApplication;
class ZLTizenApplicationWindow;

class ZLTizenViewWidget : public ZLViewWidget {
public:
	ZLTizenViewWidget(ZLApplication *application, ZLView::Angle initialAngle);
	virtual ~ZLTizenViewWidget();

	virtual void repaint();
	ZLApplication *myApplication;
	ZLTizenApplicationWindow *myWindow;
	//ZLTizenPaintContext *tizenContext;
	//Evas_Object *scroller;
	bool necessaryBoundsChecking = true;
	Evas_Object *main_layout;

	Evas_Object *image;
	Evas_Object *image2;
	Evas_Object *image3;
	Elm_Object_Item *naviframe_item;
	void draw();

	void test_draw_on_cairo(Evas_Object *image);
	void checkFirstPageOfBook();
	void checkLastPageOfBook();
};

#endif /* ZLTIZENVIEWWIDGET_H_ */
