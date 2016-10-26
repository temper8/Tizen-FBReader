/*
 * TizenColorOptionView.h
 *
 *  Created on: Oct 22, 2016
 *      Author: Alex
 */

#ifndef TIZENCOLOROPTIONVIEW_H_
#define TIZENCOLOROPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenColorOptionView: public ZLTizenOptionView {
public:

	TizenColorOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);
//	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual Evas_Object* createViewItem(Evas_Object *parent);

	Evas_Object* create_scroller(Evas_Object *parent);
	Evas_Object* create_colorselector(Evas_Object *parent);

	void setOptionColor(int r, int g, int b);

protected:
	Evas_Object *bg;
	void _createItem();
	void _onAccept() const;
};




#endif /* TIZENCOLOROPTIONVIEW_H_ */
