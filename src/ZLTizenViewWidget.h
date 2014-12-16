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

class ZLTizenViewWidget : public ZLViewWidget {
public:
	ZLTizenViewWidget(ZLApplication *application, ZLView::Angle initialAngle);
	virtual ~ZLTizenViewWidget();

	virtual void repaint();
	ZLApplication *myApplication;

	//ZLTizenPaintContext *tizenContext;
	Evas_Object *scroller;
	Evas_Object *image;
	void draw();
	void updateImage();
	void test_draw_on_cairo(Evas_Object *image);
};

#endif /* ZLTIZENVIEWWIDGET_H_ */
