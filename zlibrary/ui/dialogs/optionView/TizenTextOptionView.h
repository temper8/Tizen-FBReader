/*
 * TizenTextOptionView.h
 *
 *  Created on: Feb 17, 2015
 *      Author: alex
 */

#ifndef TIZENTEXTOPTIONVIEW_H_
#define TIZENTEXTOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenTextOptionView: public ZLTizenOptionView {
public:

	TizenTextOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);
//	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual Evas_Object* createViewItem(Evas_Object *parent);
	Evas_Object* createTestAlignment(Evas_Object *parent);

protected:
	void _createItem();
	void _onAccept() const;
};

#endif /* TIZENTEXTOPTIONVIEW_H_ */
