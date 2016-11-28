/*
 * ZLTizenCairo.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: Alex
 */

#include "ZLTizenCairo.h"
#include "../image/ZLTizenImageManager.h"

#include "logger.h"

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


void ZLTizenCairo::drawImage(int x, int y, const ZLImageData &image){
	DBG("drawImage ");
	cairo_surface_t *surface = 	((ZLTizenImageData&)image).surface;
    int imageWidth = image.width();
    int imageHeight = image.height();
	DBG("draw image w = %d, h = %d", imageWidth, imageHeight);
	cairo_set_source_surface (cairo, surface, x, y);
	cairo_paint (cairo);
}

void ZLTizenCairo::drawImage(int x, int y, const ZLImageData &image, int width, int height){
	DBG("drawImage with scaling");
	cairo_surface_t *surface = 	((ZLTizenImageData&)image).surface;
//	DBG("drawIimage x = %d, y = %d", x, y);

	int origWidth = image.width();
	int origHeight = image.height();
//	DBG("draw origWidth = %d, origHeight = %d", origWidth, origHeight);

	int realWidth = width;// imageWidth(image, width, height, type);
	int realHeight = height;//imageHeight(image, width, height, type);
//	DBG("draw realWidth = %d, realHeight = %d", realWidth, realHeight);
//	DBG("draw image width = %d, height = %d", width, height);
	cairo_save(cairo);
	cairo_translate(cairo,x,y-realHeight);
	cairo_scale(cairo, (double)realWidth/(double)origWidth, (double)realHeight/(double)origHeight);
	cairo_set_source_surface (cairo, surface, 0, 0);
	cairo_paint (cairo);
	cairo_restore(cairo);
}
