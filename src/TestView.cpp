/*
 * TestView.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: Alex
 */

#include "TestView.h"

#include "ZLPaintContext.h"

TestView::TestView(ZLPaintContext &context) : ZLView(context) {
	// TODO Auto-generated constructor stub

}

TestView::~TestView() {
	// TODO Auto-generated destructor stub
}

void TestView::paint() {
	//ReadImage();

	context().clear(ZLColor(255, 255, 255));

	int cx = 300;
	int cy = 300;
    int h,w;

    h = context().height();
    w = context().width();

    //this->context().setFillColor(ZLColor(240, 240, 240));
   	//this->context().fillRectangle(20,20,w-20,h-20);
   //	this->context().drawImage(20,20, *testImageData);
   	//this->context().drawImage(200,300, *testImageData,100,100,ZLPaintContext::SCALE_FIT_TO_SIZE);

    context().setColor(ZLColor(127, 127, 127));
	context().drawLine(10, 10, 200, 400);

	context().setColor(ZLColor(0, 255, 0));
	context().drawLine(500, 10, 10, 500);

	context().setFillColor(ZLColor(200, 0, 0));
	context().fillRectangle(cx-60,cy-60, cx+60, cy+60);



	context().setFillColor(ZLColor(0, 0, 50));
	context().drawFilledCircle(cx,cy,60);

	context().setFillColor(ZLColor(200, 200, 0));
	context().fillRectangle(cx-150, cy-150,cx-50,cy-50);

	context().setFont("Sans",40, false,false);
	context().setColor(ZLColor(0, 0, 255));
	context().drawString(20,50,"Text Русский 40",10,0);

	context().setFont("Sans",30, false, true);
	context().setColor(ZLColor(0, 0, 255));
	context().drawString(20,100,"Text Русский 30 italic",10,0);


	context().setFont("Sans",30, true,false);
	context().setColor(ZLColor(0, 255, 255));
	context().drawString(20,150,"Text Русский 30 bold",10,0);

	context().setFont("Sans",30, true, true);

	context().setFillColor(ZLColor(00, 200, 100));
	context().fillRectangle(20, 200 + context().descent(), 20 + context().stringWidth("Text Русский 30 bold italic", 27, 0) ,200 - context().stringHeight());

	context().setFillColor(ZLColor(00, 200, 0));
	context().fillRectangle(20, 200, 20 + context().stringWidth("Text Русский 30 bold italic", 27, 0) ,200 - context().stringHeight());

	context().setColor(ZLColor(255, 255, 255));
	context().drawString(20, 200,"Text Русский 30 bold italic",10,0);

}
