/*
 * ZLTizenPaintContext.h
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#ifndef ZLTIZENPAINTCONTEXT_H_
#define ZLTIZENPAINTCONTEXT_H_

#include <cairo.h>

#include "ZLPaintContext.h"

class ZLTizenPaintContext :  public ZLPaintContext {
public:
	ZLTizenPaintContext();
	virtual ~ZLTizenPaintContext();

    int width;
    int height;

    cairo_t *cairo;
    cairo_surface_t *surface;

};

#endif /* ZLTIZENPAINTCONTEXT_H_ */
