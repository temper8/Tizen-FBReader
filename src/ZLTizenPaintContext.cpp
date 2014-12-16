/*
 * ZLTizenPaintContext.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#include "ZLTizenPaintContext.h"

ZLTizenPaintContext::ZLTizenPaintContext() : ZLPaintContext() {
	// TODO Auto-generated constructor stub

}

ZLTizenPaintContext::~ZLTizenPaintContext() {
	// TODO Auto-generated destructor stub
}

void ZLTizenPaintContext::init_cairo(Evas_Object *image){
	 myImage = image;
	 int w,h;
	 evas_object_geometry_get(image, NULL, NULL, &w, &h);
	 evas_object_image_size_set(image, w, h);
	 evas_object_image_fill_set(image, 0, 0, w, h);

	 myWidth = w;
	 myHeight = h;

	 surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
	 cairo = cairo_create(surface);
}

void ZLTizenPaintContext::flush_cairo(){
	 evas_object_image_data_set(myImage, cairo_image_surface_get_data(surface));
	 evas_object_image_data_update_add(myImage, 0, 0, myWidth, myHeight);
}

int ZLTizenPaintContext::width() const{
	return myWidth;
}
int ZLTizenPaintContext::height() const{
	return myHeight;
}

void ZLTizenPaintContext::clear(ZLColor color){
	 cairo_set_source_rgb(cairo, 0.5, 0.5, 1.0);
	 cairo_paint(cairo);
}

void ZLTizenPaintContext::setColor(ZLColor color, LineStyle style){
	 cairo_set_source_rgb(cairo, color.Red / 255.0, color.Green /255.0, color.Blue / 255.0);
}
//virtual void setFillColor(ZLColor color, FillStyle style = SOLID_FILL) = 0;
void ZLTizenPaintContext::drawLine(int x0, int y0, int x1, int y1){
	 cairo_set_source_rgb(cairo, 1.0,0.0,0.5);
	 cairo_set_line_width(cairo, 1);
	 cairo_move_to(cairo, x0, y0);
	 cairo_line_to(cairo, x1, y1);
	 cairo_stroke(cairo);
}
