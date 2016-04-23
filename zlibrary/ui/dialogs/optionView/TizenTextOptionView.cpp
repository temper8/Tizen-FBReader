/*
 * TizenTextOptionView.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: alex
 */

#include "TizenTextOptionView.h"
#include "../ZLTizenOptionsDialog.h"

#include "logger.h"



TizenTextOptionView::TizenTextOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TizenTextOptionView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
//	 myTab->myTizenOptionsDialog->addEvasViewItem(createTestAlignment(tab->myTizenOptionsDialog->myBox));
}

static void app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, edj_path_max, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}


#define EDJ_FILE "edje/text.edj"

Evas_Object* TizenTextOptionView::createViewItem(Evas_Object *parent){
	char edj_path[PATH_MAX] = {0, };

	Evas_Object * label, *label2;
	Evas_Object *layout = elm_layout_add(parent);


	app_get_resource(EDJ_FILE, edj_path, (int)PATH_MAX);
	if (elm_layout_file_set(layout, edj_path, "textOptionView_layout") == 0)
				DBG("error set layout ");

//	if (elm_layout_file_set(layout, myTab->myTizenOptionsDialog->edj_path, "textOptionView_layout") == 0)
//			DBG("error set layout ");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);

	elm_object_part_text_set(layout, "title_text", _(name().c_str()));

	std::string text = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
	elm_object_part_text_set(layout, "text", _(text.c_str()));

//	label2 = elm_label_add(layout);
//	elm_object_part_content_set(layout, "text", label2);
//	elm_label_line_wrap_set(label2, ELM_WRAP_MIXED);
//	elm_label_wrap_width_set(label2, 100);

//	std::string text = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
//	elm_object_text_set(label2, _(text.c_str()));
//	elm_object_content_set(layout,label2);
//	evas_object_show(label);

	return layout;
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
