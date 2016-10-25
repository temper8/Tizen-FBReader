/*
 * TizenBooleanOptionView.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: Alex
 */

#include "TizenBooleanOptionView.h"
#include "../ZLTizenOptionsDialog.h"

#include "../ZLTizen.h"
#include "logger.h"

TizenBooleanOptionView::TizenBooleanOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TizenBooleanOptionView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
}


static void check_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	TizenBooleanOptionView *myBoolean = (TizenBooleanOptionView *)data;

	Eina_Bool state = elm_check_state_get(obj);

	switch(state){
	case EINA_TRUE :
		myBoolean->setOptionValue(true);
		break;
	case EINA_FALSE :
		myBoolean->setOptionValue(false);
		break;
	default:
		break;
	}

}

bool TizenBooleanOptionView::getOptionValue(){
	return ((ZLBooleanOptionEntry&)*myOption).initialState();
}

void TizenBooleanOptionView::setOptionValue(bool state){

	((ZLBooleanOptionEntry&)*myOption).onAccept(state);
}

Evas_Object* TizenBooleanOptionView::createViewItem(Evas_Object *parent){

	Evas_Object *check;
	Evas_Object *layout = elm_layout_add(parent);

	ZLTizenUtil::layout_edj_set(layout, "fbr.BooleanOptionView");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);

	check = elm_check_add(layout);
	elm_object_style_set(check, "on&off");
	elm_check_state_set(check, (getOptionValue())?EINA_TRUE:EINA_FALSE);

	elm_object_part_content_set(layout, "check", check);
	evas_object_smart_callback_add(check, "changed", check_changed_cb, this);


	elm_object_part_text_set(layout, "caption", _(name().c_str()));

	return layout;
}

void TizenBooleanOptionView::_createItem() {
	 myCaption = ZLOptionView::name();
}

void TizenBooleanOptionView::_onAccept() const { }


