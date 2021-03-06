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


	int width() const;
	int height() const;

	void clear(ZLColor color);

	void setFont(const std::string &family, int size, bool bold, bool italic);
	void setColor(ZLColor color, LineStyle style = SOLID_LINE);
	void setFillColor(ZLColor color, FillStyle style = SOLID_FILL);

	void drawLine(int x0, int y0, int x1, int y1);
	void fillRectangle(int x0, int y0, int x1, int y1);
	void drawFilledCircle(int x, int y, int r);

	void drawImage(int x, int y, const ZLImageData &image);
	void drawImage(int x, int y, const ZLImageData &image, int width, int height, ScalingType type);


	int stringWidth(const char *str, int len, bool rtl) const;
	int spaceWidth() const;
	int stringHeight() const;
	int descent() const;
	void drawString(int x, int y, const char *str, int len, bool rtl);

	const std::string realFontFamilyName(std::string &fontFamily) const;

    cairo_t *cairo = 0;
    cairo_surface_t *surface = 0;
    Evas_Object *myImage;
    void init_cairo(Evas_Object *image);
    void flush_cairo();

protected:
    void fillFamiliesList(std::vector<std::string> &families) const;

private:

    int myWidth = 0;
    int myHeight = 0;


	ZLColor myFillColor;
	ZLColor myPenColor;

	std::vector<std::string> myFontFamilies;

	mutable int myStringHeight;
	mutable int mySpaceWidth;
	int myDescent;

};

#endif /* ZLTIZENPAINTCONTEXT_H_ */
