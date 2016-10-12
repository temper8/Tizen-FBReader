/*
 * TizenTextOptionView.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: alex
 */

#include "TizenTextOptionView.h"
#include "../ZLTizenOptionsDialog.h"

#include "../ZLTizen.h"
#include "logger.h"


TizenTextOptionView::TizenTextOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TizenTextOptionView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
//	 myTab->myTizenOptionsDialog->addEvasViewItem(createTestAlignment(tab->myTizenOptionsDialog->myBox));
}


Evas_Object* TizenTextOptionView::createViewItem(Evas_Object *parent){

	Evas_Object *layout = elm_layout_add(parent);

	ZLTizenUtil::layout_edj_set(layout, "fbr.TextOptionView");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND,  0.0);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);

	Evas_Object *label = elm_label_add(layout);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0.0);

	elm_object_part_text_set(layout, "title_text", _(name().c_str()));

	std::string text = ((ZLStaticTextOptionEntry&)*myOption).initialValue();

	elm_object_part_text_set(layout, "text", _(text.c_str()));

	elm_label_line_wrap_set(label, ELM_WRAP_MIXED);
	text = "<font_size=40>" + text + "</font_size>";
	elm_object_text_set(label,_(text.c_str()));
	elm_object_part_content_set(layout, "YShYCZgm", label);

//	label2 = elm_label_add(layout);
//	elm_object_part_content_set(layout, "text", label2);
//	elm_label_line_wrap_set(label2, ELM_WRAP_MIXED);
//	elm_label_wrap_width_set(label2, 100);

//	std::string text = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
//	elm_object_text_set(label2, _(text.c_str()));
//	elm_object_content_set(layout,label2);
//	evas_object_show(label);

	return layout;
//	return label;
}

void TizenTextOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
}

void TizenTextOptionView::_onAccept() const { }

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
