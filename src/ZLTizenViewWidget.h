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

class ZLApplication;

class ZLTizenViewWidget : public ZLViewWidget {
public:
	ZLTizenViewWidget(ZLApplication *application, ZLView::Angle initialAngle);
	virtual ~ZLTizenViewWidget();

	virtual void repaint();
	ZLApplication *myApplication;
};

#endif /* ZLTIZENVIEWWIDGET_H_ */
