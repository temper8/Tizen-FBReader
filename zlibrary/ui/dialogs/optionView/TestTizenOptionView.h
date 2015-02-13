/*
 * TestTizenOptionView.h
 *
 *  Created on: Aug 8, 2013
 *      Author: temper8
 */

#ifndef TESTTIZENOPTIONVIEW_H_
#define TESTTIZENOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TestTizenOptionView: public ZLTizenOptionView {
public:

	TestTizenOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);
//	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual Evas_Object* createViewItem(Evas_Object *parent);
protected:
	void _createItem();
	void _onAccept() const;
};

#endif /* TESTTIZENOPTIONVIEW_H_ */
