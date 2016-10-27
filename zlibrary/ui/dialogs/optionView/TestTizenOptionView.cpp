/*
 * TestTizenOptionView.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: temper8
 */

#include "TestTizenOptionView.h"
#include "../ZLTizenOptionsDialog.h"

#include "logger.h"

#define EDJ_FILE "/opt/usr/apps/org.tizen.tizen-fbreader/res/edje/alignment.edj"

TestTizenOptionView::TestTizenOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TestTizenOptionView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
//	 myTab->myTizenOptionsDialog->addEvasViewItem(createTestAlignment(tab->myTizenOptionsDialog->myBox));
}

Evas_Object* TestTizenOptionView::createTestAlignment(Evas_Object *parent){
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
elm_object_text_set(label, _("<align=left><b>TestTizenOptionView</b></align>"));
//	evas_object_show(label);

return layout;
}

Evas_Object* TestTizenOptionView::createViewItem(Evas_Object *parent){
	Evas_Object * label, *label2;
	Evas_Object *layout = elm_layout_add(parent);

	// old if (elm_layout_file_set(layout, myTab->myTizenOptionsDialog->edj_path, "test_layout") == 0)
			DBG("error set layout ");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	label = elm_label_add(layout);
	elm_object_part_content_set(layout, "title", label);
	//evas_object_move(label, 1, 1);
//	evas_object_resize(label, 300, 45);
	elm_object_text_set(label, _("<align=left><b>TestTizenOptionView</b></align>"));
//	evas_object_show(label);

	label2 = elm_label_add(layout);
	elm_object_part_content_set(layout, "text_string", label2);
	elm_object_text_set(label2, _(name().c_str()));
	elm_object_content_set(layout,label2);
//	evas_object_show(label);

	return layout;
}

void TestTizenOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
}

void TestTizenOptionView::_onAccept() const { }

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
