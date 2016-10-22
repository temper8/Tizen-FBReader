/*
 * TizenColorOptionView.cpp
 *
 *  Created on: Oct 22, 2016
 *      Author: Alex
 */


#include "TizenColorOptionView.h"
#include "../ZLTizenOptionsDialog.h"

#include "../ZLTizen.h"
#include "logger.h"

TizenColorOptionView::TizenColorOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TestTizenOptioTizenColorOptionViewnView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
}

Evas_Object* TizenColorOptionView::createViewItem(Evas_Object *parent){

	Evas_Object *layout = elm_layout_add(parent);

	ZLTizenUtil::layout_edj_set(layout, "fbr.ColorOptionView");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);

	Evas_Object *bg = elm_bg_add(layout);
	ZLColor myColor = ((ZLColorOptionEntry&)*myOption).color();
	elm_bg_color_set(bg, myColor.Red, myColor.Green, myColor.Blue);
	elm_object_part_content_set(layout, "color", bg);

	elm_object_part_text_set(layout, "caption", _(name().c_str()));

	return layout;
}


void TizenColorOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();

}

void TizenColorOptionView::_onAccept() const { }
