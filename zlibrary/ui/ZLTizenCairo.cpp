/*
 * ZLTizenCairo.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: Alex
 */

#include "ZLTizenCairo.h"

ZLTizenCairo::ZLTizenCairo(Evas_Object *image){
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


void ZLTizenCairo::flush_cairo(){
	 evas_object_image_data_set(myImage, cairo_image_surface_get_data(surface));
	 evas_object_image_data_update_add(myImage, 0, 0, myWidth, myHeight);
}

int ZLTizenCairo::width() const{
	return myWidth;
}
int ZLTizenCairo::height() const{
	return myHeight;
}

void ZLTizenCairo::clear(ZLColor color){
	 cairo_set_source_rgb(cairo, (double)color.Red / 255.0, (double)color.Green / 255.0, (double)color.Blue / 255.0);
	 cairo_paint(cairo);
}

