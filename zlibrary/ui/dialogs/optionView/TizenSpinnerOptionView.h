/*
 * TizenSpinnerOptionView.h
 *
 *  Created on: Feb 26, 2015
 *      Author: alex
 */

#ifndef TIZENSPINNEROPTIONVIEW_H_
#define TIZENSPINNEROPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenSpinnerOptionView: public ZLTizenOptionView {
public:

	TizenSpinnerOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);
//	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual Evas_Object* createViewItem(Evas_Object *parent);
	Evas_Object* createTestAlignment(Evas_Object *parent);

protected:
	int minValue;
	int maxValue;
	void _createItem();
	void _onAccept() const;
};

#endif /* TIZENSPINNEROPTIONVIEW_H_ */
