/*
 * TizenComboOptionView.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: Alex
 */


#include "TizenComboOptionView.h"
#include "../ZLTizenOptionsDialog.h"

#include "logger.h"

//#define EDJ_FILE "/opt/usr/apps/org.tizen.tizen-fbreader/res/edje/alignment.edj"

TizenComboOptionView::TizenComboOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TizenComboOptionView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
}

static void app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, edj_path_max, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}


//#define EDJ_FILE "edje/text.edj"
#define EDJ_FILE "edje/xxx.edj"

Evas_Object* TizenComboOptionView::createViewItem(Evas_Object *parent){

	char edj_path[PATH_MAX] = {0, };

	Evas_Object *check;
	Evas_Object *layout = elm_layout_add(parent);

	app_get_resource(EDJ_FILE, edj_path, (int)PATH_MAX);
	if (elm_layout_file_set(layout, edj_path, "comboOptionView") == 0)
				DBG("error set layout ");

	//if (elm_layout_file_set(layout, myTab->myTizenOptionsDialog->edj_path, "booleantOptionView") == 0)
	//		DBG("error set layout ");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);

/*	check = elm_check_add(layout);
	//elm_object_text_set(check, "Default");
	elm_object_style_set(check, "on&off");
	elm_check_state_set(check, EINA_TRUE);

	elm_object_part_content_set(layout, "check", check);
*/
	elm_object_part_text_set(layout, "caption", _(name().c_str()));


//	elm_object_text_set(label, _("<align=left><b>TizenBooleanOptionView</b></align>"));



	return layout;
}

void TizenComboOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
}

void TizenComboOptionView::_onAccept() const { }





