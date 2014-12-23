/*
 * TestView.h
 *
 *  Created on: Dec 12, 2014
 *      Author: Alex
 */

#ifndef TESTVIEW_H_
#define TESTVIEW_H_

#include "ZLView.h"

class TestView : public ZLView {
public:
	TestView(ZLPaintContext &context);
	virtual ~TestView();
	const std::string &caption() const;
	virtual void paint();

public:
	static const ZLTypeId TYPE_ID;

private:
	const ZLTypeId &typeId() const;

};

#endif /* TESTVIEW_H_ */
