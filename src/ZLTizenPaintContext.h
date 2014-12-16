/*
 * ZLTizenPaintContext.h
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#ifndef ZLTIZENPAINTCONTEXT_H_
#define ZLTIZENPAINTCONTEXT_H_

#include <cairo.h>
#include <efl_extension.h>

#include "ZLPaintContext.h"

class ZLTizenPaintContext :  public ZLPaintContext {
public:
	ZLTizenPaintContext();
	virtual ~ZLTizenPaintContext();

	void clear(ZLColor color);

	//virtual void setFont(const std::string &family, int size, bool bold, bool italic) = 0;
	void setColor(ZLColor color, LineStyle style = SOLID_LINE);
	//virtual void setFillColor(ZLColor color, FillStyle style = SOLID_FILL) = 0;
	int width() const;
	int height() const;
	void drawLine(int x0, int y0, int x1, int y1);

    int myWidth;
    int myHeight;

    cairo_t *cairo;
    cairo_surface_t *surface;
    Evas_Object *myImage;
    void init_cairo(Evas_Object *image);
    void flush_cairo();
};

#endif /* ZLTIZENPAINTCONTEXT_H_ */
