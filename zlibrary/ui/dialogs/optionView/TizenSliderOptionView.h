/*
 * TizenSliderOptionView.h
 *
 *  Created on: Feb 26, 2015
 *      Author: alex
 */

#ifndef TIZENSLIDEROPTIONVIEW_H_
#define TIZENSLIDEROPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenSliderOptionView: public ZLTizenOptionView {
public:
	Evas_Object *layout;
	TizenSliderOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);
//	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual Evas_Object* createViewItem(Evas_Object *parent);
	//Evas_Object* createTestAlignment(Evas_Object *parent);

	void accept(int value);

protected:
	int minValue;
	int maxValue;
	void _createItem();
	void _onAccept() const;

};

#endif /* TIZENSLIDEROPTIONVIEW_H_ */
