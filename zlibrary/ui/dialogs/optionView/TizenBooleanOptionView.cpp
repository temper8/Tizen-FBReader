/*
 * TizenBooleanOptionView.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: alex
 */

#include "TizenBooleanOptionView.h"


#include "../ZLTizenOptionsDialog.h"

#include "logger.h"

#define EDJ_FILE "/opt/usr/apps/org.tizen.tizen-fbreader/res/edje/alignment.edj"

TizenBooleanOptionView::TizenBooleanOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TizenBooleanOptionView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
//	 myTab->myTizenOptionsDialog->addEvasViewItem(createTestAlignment(tab->myTizenOptionsDialog->myBox));
}

Evas_Object* TizenBooleanOptionView::createTestAlignment(Evas_Object *parent){
/* Base Layout */

Evas_Object *layout = elm_layout_add(parent);
if (elm_layout_file_set(layout, EDJ_FILE, "main") == 0) DBG("createTestAlignment error set layout ");
evas_object_size_hint_min_set(layout, 400,400);
//evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//elm_object_content_set(parent, layout);
Evas_Object *label = elm_label_add(layout);
elm_object_part_content_set(layout, "button1", label);
//evas_object_move(label, 1, 1);
//	evas_object_resize(label, 300, 45);
elm_object_text_set(label, _("<align=left><b>TizenBooleanOptionView</b></align>"));
//	evas_object_show(label);

return layout;
}

Evas_Object* TizenBooleanOptionView::createViewItem(Evas_Object *parent){
	Evas_Object * label, *label2, *check;
	Evas_Object *layout = elm_layout_add(parent);

	if (elm_layout_file_set(layout, myTab->myTizenOptionsDialog->edj_path, "boolean_layout") == 0)
			DBG("error set layout ");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

//	label = elm_label_add(layout);
//	elm_object_part_content_set(layout, "title", label);
	//evas_object_move(label, 1, 1);
//	evas_object_resize(label, 300, 45);
//	elm_object_text_set(label, _("<align=left><b>TizenBooleanOptionView</b></align>"));
//	evas_object_show(label);

	label2 = elm_label_add(layout);
	elm_object_part_content_set(layout, "title", label2);
	elm_object_text_set(label2, _(name().c_str()));
	elm_object_content_set(layout,label2);
//	evas_object_show(label);
	/* check 2 */
	check = elm_check_add(layout);
	elm_object_part_content_set(layout, "text_string", check);
	elm_object_style_set(check, "on&off");
	elm_check_state_set(check, EINA_FALSE);
//	elm_object_part_content_set(layout, "check3", check);
//	evas_object_smart_callback_add(check, "changed", check_changed_cb, (void *)3);

	return layout;
}

void TizenBooleanOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
}

void TizenBooleanOptionView::_onAccept() const { }

/*
TableViewItem* TestTizenOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, defaultItemHeight), style);

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight), myCaption);

	pItem->AddControl(pLabel);

	return pItem;
}*/
