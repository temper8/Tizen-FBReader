/*
 * ZLTizenImageManager.cpp
 *
 *  Created on: Feb 18, 2015
 *      Author: alex
 */
#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>

#include <ZLImage.h>

#include "ZLTizenImageManager.h"
#include <image_util.h>

#include "logger.h"

ZLTizenImageData::ZLTizenImageData(): myX(0), myY(0), surface(NULL){

}

ZLTizenImageData::~ZLTizenImageData() {
	if (surface != NULL) {
		cairo_surface_destroy(surface);
	}
}

unsigned int ZLTizenImageData::width() const {
	return (surface != NULL)  ? cairo_image_surface_get_width(surface)   : 0;
}

unsigned int ZLTizenImageData::height() const {
	return (surface != NULL)  ? cairo_image_surface_get_height(surface) : 0;
}

void ZLTizenImageData::init(unsigned int width, unsigned int height) {
	if (surface != NULL) {
		cairo_surface_destroy(surface);
	}
	DBG("new surface %d %d",width,height );
//	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, heigh);
	//pImage = new QImage(width, height, QImage::Format_RGB32);
//	AppLog("new Bitmap %d %d",width,height );
	// pBitmap = new Bitmap();
     // Construct Bitmap without buffer scaling.
   //  pBitmap->Construct(Dimension(width, height), BITMAP_PIXEL_FORMAT_ARGB8888);


}

void ZLTizenImageData::setPosition(unsigned int x, unsigned int y) {
	myX = x;
	myY = y;
}

void ZLTizenImageData::moveX(int delta) {
	myX += delta;
}

void ZLTizenImageData::moveY(int delta) {
	myY += delta;
}

void ZLTizenImageData::setPixel(unsigned char r, unsigned char g, unsigned char b) {
//	myImage->setPixel(myX, myY, qRgb(r, g, b));
}

void ZLTizenImageData::copyFrom(const ZLImageData &source, unsigned int targetX, unsigned int targetY) {
//	const QImage *sourceImage = ((const ZLTizenImageData*)&source)->image();
//	if ((myImage != 0) && (sourceImage != 0)) {
//		QPainter painter(myImage);
//		painter.drawImage(targetX, targetY, *sourceImage);
//	}
}

shared_ptr<ZLImageData> ZLTizenImageManager::createData() const {
	DBG("ZLTizenImageManager::createData() ");
	return new ZLTizenImageData();
}
typedef struct closure_data
{
	 const  unsigned char *buff;
	 int length;
	 int pos;
} closure_data_s;

static cairo_status_t  cairo_read_func(void *closure,  unsigned char *data,    unsigned int length){
	closure_data_s* c = (closure_data_s *)closure;
//	DBG("cairo_read_func %d", length);
	if (c->pos + length > c->length)
	    return CAIRO_STATUS_READ_ERROR;
    memcpy (data, c->buff + c->pos, length);
	  c->pos += length;
	return CAIRO_STATUS_SUCCESS;
}

bool ZLTizenImageManager::convertImageDirect(const std::string &stringData, ZLImageData &data) const {
	DBG("convertImageDirect");
	int imageWidth=100;
	int imageHeight=100;
    if (strncmp(stringData.data()+1, "PNG", 3) == 0) {
    	DBG("format = IMG_FORMAT_PNG" );
    	closure_data_s c;
    	c.buff = (unsigned char *) stringData.data();
    	c.pos = 0;
    	c.length = stringData.length();
    	((ZLTizenImageData&)data).surface = cairo_image_surface_create_from_png_stream(cairo_read_func, (void *)&c);
		if (((ZLTizenImageData&)data).surface!=NULL) DBG("surface created");
												else DBG("surface error");
		return true;
    }
    else
    if (strncmp(stringData.data(), "GIF", 3) == 0) {
        	DBG("format = IMG_FORMAT_GIF" );
    //    	iformat = IMG_FORMAT_GIF;
        }
    else {
   // 	iformat = IMG_FORMAT_JPG;
    	DBG("iformat = IMG_FORMAT_JPG" );
    	unsigned int imageSize;
    	image_util_calculate_buffer_size(imageWidth, imageHeight, IMAGE_UTIL_COLORSPACE_ARGB8888, &imageSize );
    	DBG("image Size %d", imageSize);
    	unsigned char ** imageBuffer;
    	int res =image_util_decode_jpeg_from_memory(( unsigned char *)stringData.data(), stringData.length(), IMAGE_UTIL_COLORSPACE_BGRA8888,	imageBuffer, &imageWidth, &imageHeight, &imageSize);
		DBG("r =%d w = %d h = %d s = %d",res, imageWidth,imageHeight,imageSize);
		//DBG("new surface %d %d",width,height );
		int stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24,imageWidth);
		DBG("stride =%d", stride);
		// оказалось что IMAGE_UTIL_COLORSPACE_BGRA8888 == CAIRO_FORMAT_RGB24
		((ZLTizenImageData&)data).surface = cairo_image_surface_create_for_data(*imageBuffer, CAIRO_FORMAT_RGB24, imageWidth, imageHeight, stride);
		if (((ZLTizenImageData&)data).surface!=NULL) DBG("surface created");
												else DBG("surface error");
		return true;
    }
return true;
}
