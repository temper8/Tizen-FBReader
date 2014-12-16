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

    int h,w;
    h = context().height();
    w = context().width();

    //this->context().setFillColor(ZLColor(240, 240, 240));
   	//this->context().fillRectangle(20,20,w-20,h-20);
   //	this->context().drawImage(20,20, *testImageData);
   	//this->context().drawImage(200,300, *testImageData,100,100,ZLPaintContext::SCALE_FIT_TO_SIZE);

    context().setColor(ZLColor(127, 127, 127));
	context().drawLine(10, 10, 200, 400);

	//this->context().setColor(ZLColor(0, 255, 0));
	//this->context().drawLine(10, 600, 200+ (Math::Rand() % (200)), 100+ (Math::Rand() % (200)));

	//this->context().setFillColor(ZLColor(200, 0, 0));
	//this->context().fillRectangle(CircleXY.x-50,CircleXY.y-50,CircleXY.x+50,CircleXY.y+50);

	//this->context().setFillColor(ZLColor(200, 200, 0));
	//this->context().fillRectangle(CircleXY.x-25,CircleXY.y-25,CircleXY.x+75,CircleXY.y+75);

	//this->context().setColor(ZLColor(0, 0, 0));
	//this->context().drawFilledCircle(CircleXY.x,CircleXY.y,60);

	//this->context().setColor(ZLColor(0, 0, 255));
	//this->context().drawString(CircleXY.x-20,CircleXY.y-0,"TextРусский",10,0);

}
