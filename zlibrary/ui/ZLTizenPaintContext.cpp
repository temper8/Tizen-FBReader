/*
 * ZLTizenPaintContext.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#include "ZLTizenPaintContext.h"

#include "eina_unicode.h"
#include "logger.h"

#include <libxml/xmlexports.h>

#include <libxml/parser.h>

#include "image/ZLTizenImageManager.h"

ZLTizenPaintContext::ZLTizenPaintContext() : ZLPaintContext() {
	// TODO Auto-generated constructor stub
	mySpaceWidth = -1;
}

ZLTizenPaintContext::~ZLTizenPaintContext() {
	// TODO Auto-generated destructor stub
}

void ZLTizenPaintContext::init_cairo(Evas_Object *image){
	 myImage = image;
	 int w,h;
	 evas_object_geometry_get(image, NULL, NULL, &w, &h);

  //   if (!((myWidth == w)&&(myHeight == h))) {
    	 evas_object_image_size_set(image, w, h);
    	 evas_object_image_fill_set(image, 0, 0, w, h);
    	 myWidth = w;
    	 myHeight = h;
  //   }
     int row_stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, w);
     unsigned char *imageData = (unsigned char *)evas_object_image_data_get(image, EINA_TRUE);
     surface = cairo_image_surface_create_for_data(imageData, CAIRO_FORMAT_ARGB32, w, h, row_stride);
     cairo = cairo_create(surface);

	 //if (surface != NULL) cairo_surface_destroy(surface);
	 //surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
	// cairo = cairo_create(surface);
}

void ZLTizenPaintContext::flush_cairo(){
	 evas_object_image_data_set(myImage, cairo_image_surface_get_data(surface));
	 evas_object_image_data_update_add(myImage, 0, 0, myWidth, myHeight);
	 cairo_surface_destroy(surface);
}

int ZLTizenPaintContext::width() const{
	return myWidth;
}
int ZLTizenPaintContext::height() const{
	return myHeight;
}

void ZLTizenPaintContext::clear(ZLColor color){
	 cairo_set_source_rgb(cairo, (double)color.Red / 255.0, (double)color.Green / 255.0, (double)color.Blue / 255.0);
	 cairo_paint(cairo);
}

void ZLTizenPaintContext::setColor(ZLColor color, LineStyle style){
	myPenColor = color;

}

void ZLTizenPaintContext::setFillColor(ZLColor color, FillStyle style){
	myFillColor = color;
}

void ZLTizenPaintContext::drawLine(int x0, int y0, int x1, int y1){
	 cairo_set_source_rgb(cairo, myPenColor.Red / 255.0, myPenColor.Green /255.0, myPenColor.Blue / 255.0);
	 //cairo_set_source_rgb(cairo, 1.0,0.0,0.5);
	 cairo_set_line_width(cairo, 1);
	 cairo_move_to(cairo, x0, y0);
	 cairo_line_to(cairo, x1, y1);
	 cairo_stroke(cairo);
}


void ZLTizenPaintContext::fillRectangle(int x0, int y0, int x1, int y1){
	 cairo_set_source_rgb(cairo, myFillColor.Red / 255.0, myFillColor.Green /255.0, myFillColor.Blue / 255.0);
	 int x,y,w,h;
	 if (x1>x0) { x = x0; w = x1-x0;}
	 else { x = x1; w = x0-x1;}
	 if (y1>y0) { y = y0; h = y1-y0;}
	 	 else { y = y1; h = y0-y1;}
	 cairo_rectangle (cairo, x, y, w, h);
	 cairo_fill (cairo);
}

void ZLTizenPaintContext::drawFilledCircle(int x, int y, int r){
	cairo_set_source_rgb(cairo, myFillColor.Red / 255.0, myFillColor.Green /255.0, myFillColor.Blue / 255.0);
	//cairo_translate(cairo, x, y);
	cairo_arc(cairo, x, y, r, 0, 2 * M_PI);
	cairo_fill (cairo);
	//cairo_stroke_preserve(cairo);
}

// ******************* FONT ***********

void ZLTizenPaintContext::setFont(const std::string &family, int size, bool bold, bool italic){
	cairo_select_font_face (cairo, "Sans",
			italic?CAIRO_FONT_SLANT_OBLIQUE:CAIRO_FONT_SLANT_NORMAL,
			bold?CAIRO_FONT_WEIGHT_BOLD:CAIRO_FONT_WEIGHT_NORMAL);

	cairo_set_font_size (cairo, size);

	cairo_text_extents_t extents;
	cairo_text_extents (cairo, " ", &extents);

	cairo_font_extents_t font_extents;
	cairo_font_extents (cairo, &font_extents);

	myStringHeight = font_extents.height;
	myDescent = font_extents.descent;
	mySpaceWidth = -1;//font_extents.max_x_advance;
}

int ZLTizenPaintContext::stringWidth(const char *str, int len, bool rtl) const{
	//DBG("stringWidth len = %d str =%s",len, str);
	char *utf8 = strndup(str,len);
	//DBG("stringWidth utf8 len=%d str=%s",len, utf8);
	cairo_text_extents_t extents;
	cairo_text_extents (cairo, (char* )utf8, &extents);
	delete utf8;
	return extents.width;
}

int ZLTizenPaintContext::spaceWidth() const{
//	DBG("spaceWidth");
	if (mySpaceWidth == -1) {
		cairo_text_extents_t extents;
		cairo_text_extents (cairo, "s", &extents);
		mySpaceWidth = extents.width;
	//	DBG("spaceWidth %d",mySpaceWidth);
	}
	return mySpaceWidth;
}

int ZLTizenPaintContext::stringHeight() const{
//	DBG("myStringHeight %d", myStringHeight);
	return myStringHeight;
}

int ZLTizenPaintContext::descent() const{
   return myDescent;
}

void ZLTizenPaintContext::drawString(int x, int y, const char *str, int len, bool rtl){
	cairo_set_source_rgb(cairo, myPenColor.Red / 255.0, myPenColor.Green /255.0, myPenColor.Blue / 255.0);
	cairo_move_to (cairo, x,y);

	char *utf8 = strndup(str,len);
	cairo_show_text (cairo, (char*)utf8);
	delete utf8;
}

const std::string ZLTizenPaintContext::realFontFamilyName(std::string &fontFamily) const {
	return "Sans";
}

void ZLTizenPaintContext::fillFamiliesList(std::vector<std::string> &families) const {


}

void ZLTizenPaintContext::drawImage(int x, int y, const ZLImageData &image){
	DBG("drawImage ");
	cairo_surface_t *surface = 	((ZLTizenImageData&)image).surface;
    int imageWidth = image.width();
    int imageHeight = image.height();
	DBG("draw image w = %d, h = %d", imageWidth, imageHeight);
	cairo_set_source_surface (cairo, surface, x, y);
	cairo_paint (cairo);
}

void ZLTizenPaintContext::drawImage(int x, int y, const ZLImageData &image, int width, int height, ScalingType type){
	DBG("drawImage with scaling");
	cairo_surface_t *surface = 	((ZLTizenImageData&)image).surface;
//	DBG("drawIimage x = %d, y = %d", x, y);

	int origWidth = image.width();
	int origHeight = image.height();
//	DBG("draw origWidth = %d, origHeight = %d", origWidth, origHeight);

	int realWidth = imageWidth(image, width, height, type);
	int realHeight = imageHeight(image, width, height, type);
//	DBG("draw realWidth = %d, realHeight = %d", realWidth, realHeight);
//	DBG("draw image width = %d, height = %d", width, height);
	cairo_save(cairo);
	cairo_translate(cairo,x,y-realHeight);
	cairo_scale(cairo, (double)realWidth/(double)origWidth, (double)realHeight/(double)origHeight);
	cairo_set_source_surface (cairo, surface, 0, 0);
	cairo_paint (cairo);
	cairo_restore(cairo);
}
