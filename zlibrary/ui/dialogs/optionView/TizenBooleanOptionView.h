/*
 * TizenBooleanOptionView.h
 *
 *  Created on: Apr 18, 2015
 *      Author: alex
 */

#ifndef TIZENBOOLEANOPTIONVIEW_H_
#define TIZENBOOLEANOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenBooleanOptionView: public ZLTizenOptionView {
public:

	TizenBooleanOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);
//	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual Evas_Object* createViewItem(Evas_Object *parent);
	Evas_Object* createTestAlignment(Evas_Object *parent);

protected:
	void _createItem();
	void _onAccept() const;
};
#endif /* TIZENBOOLEANOPTIONVIEW_H_ */
