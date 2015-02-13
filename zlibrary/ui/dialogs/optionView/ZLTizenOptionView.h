/*
 * ZLTizenOptionView.h
 *
 *  Created on: Aug 8, 2013
 *      Author: temper8
 */

#ifndef ZLTIZENOPTIONVIEW_H_
#define ZLTIZENOPTIONVIEW_H_

#include "ZLOptionView.h"
#include "../ZLTizenDialogContent.h"

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>

class ZLTizenOptionView: public ZLOptionView {
protected:
	ZLTizenOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLOptionView(name, tooltip, option), myTab(tab), myRow(row), myFromColumn(fromColumn), myToColumn(toColumn) {}
//	virtual ~ZLTizenOptionView();

	void _show();
	void _hide();
	void _setActive(bool active);

protected:
	int groupIndex;
	int itemIndex;
	int myRow, myFromColumn, myToColumn;
public :
	std::string myCaption;
	ZLTizenDialogContent *myTab;
	virtual bool isBoolOption() { return false; }
	virtual bool boolOptionState() { return false; }
	virtual Evas_Object* createViewItem(Evas_Object *parent) = 0;
	//virtual void OnStateChanged(Tizen::Ui::Controls::TableViewItemStatus status) {};
	//virtual void OnActionPerformed(int actionId) = 0;
};

#endif /* ZLTIZENOPTIONVIEW_H_ */
