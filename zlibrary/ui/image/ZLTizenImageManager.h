/*
 * ZLTizenImageManager.h
 *
 *  Created on: Feb 18, 2015
 *      Author: alex
 */

#ifndef ZLTIZENIMAGEMANAGER_H_
#define ZLTIZENIMAGEMANAGER_H_
#include <map>

#include <ZLImageManager.h>
#include <cairo.h>

class ZLImage;
class ZLTizenImageData : public ZLImageData {

public:
	ZLTizenImageData();
	~ZLTizenImageData();

	unsigned int width() const;
	unsigned int height() const;

	void init(unsigned int width, unsigned int height);
	void setPosition(unsigned int x, unsigned int y);
	void moveX(int delta);
	void moveY(int delta);
	void setPixel(unsigned char r, unsigned char g, unsigned char b);

	void copyFrom(const ZLImageData &source, unsigned int targetX, unsigned int targetY);

	const cairo_surface_t *image() const { return surface; }
	cairo_surface_t *surface;
	const void * getImageData();
	size_t getImageSize();

private:

	unsigned int myX, myY;

friend class ZLTizenImageManager;
};

class ZLTizenImageManager : public ZLImageManager {

public:
	static void createInstance() { ourInstance = new ZLTizenImageManager(); }

private:
	ZLTizenImageManager() {}

protected:
	~ZLTizenImageManager() {}
	shared_ptr<ZLImageData> createData() const;
	bool convertImageDirect(const std::string &stringData, ZLImageData &imageData) const;
};

#endif /* ZLTIZENIMAGEMANAGER_H_ */
