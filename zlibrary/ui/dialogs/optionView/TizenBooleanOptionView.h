/*
 * TizenBooleanOptionView.h
 *
 *  Created on: Jun 9, 2016
 *      Author: Alex
 */

#ifndef TIZENBOOLEANOPTIONVIEW_H_
#define TIZENBOOLEANOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenBooleanOptionView: public ZLTizenOptionView {
public:

	TizenBooleanOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);
//	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual Evas_Object* createViewItem(Evas_Object *parent);

	void setOptionValue(bool state);
	bool getOptionValue();
protected:
	void _createItem();
	void _onAccept() const;
};


#endif /* TIZENBOOLEANOPTIONVIEW_H_ */
