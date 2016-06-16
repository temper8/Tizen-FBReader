/*
 * TizenComboOptionView.h
 *
 *  Created on: Jun 9, 2016
 *      Author: Alex
 */

#ifndef TIZENCOMBOOPTIONVIEW_H_
#define TIZENCOMBOOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenComboOptionView: public ZLTizenOptionView {
public:

	TizenComboOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);

	shared_ptr<ZLOptionEntry> option() const 	{ return  myOption;};

//	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual Evas_Object* createViewItem(Evas_Object *parent);

protected:
	void _createItem();
	void _onAccept() const;
};


#endif /* TIZENCOMBOOPTIONVIEW_H_ */
