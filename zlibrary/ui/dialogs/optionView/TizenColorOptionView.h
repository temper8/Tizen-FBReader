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

protected:
	void _createItem();
	void _onAccept() const;
};




#endif /* TIZENCOLOROPTIONVIEW_H_ */
