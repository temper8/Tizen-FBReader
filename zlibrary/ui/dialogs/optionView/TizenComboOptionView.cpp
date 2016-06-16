/*
 * TizenComboOptionView.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: Alex
 */


#include "TizenComboOptionView.h"
#include "../ZLTizenOptionsDialog.h"
#include "../../ZLTizenApplicationWindow.h"

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

static char *items[] = {
	"Text 1line", "Text 2line", "Text 3line",
	"Text 4line", "Text 5line", "Text 6line",
	"Text 7line", "Text 8line"
};

static char*
gl_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int index = (int) data;
	return strdup(items[index]);
}


static void
gl_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = (Evas_Object *)data;
	int index = 0;
	Elm_Object_Item *item = (Elm_Object_Item *)event_info;

	index = (int)elm_object_item_data_get(item);
	printf("selected text %s\n",items[index]);
	printf("Index of the list=%d\n", index);
	evas_object_del(popup);
}
static void up_callback(void *data, Evas *e, Evas_Object *obj, void *event_info)
//static void list_it_list_cb(void *data, Evas_Object *obj, void *event_info)
{
	DBG("TizenComboOptionView---createViewItem");
	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *box;
	Evas_Object *genlist;
	int i;
	Evas_Object *win = (Evas_Object *)data;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* box */
	box = elm_box_add(popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* genlist */
	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	itc.func.text_get = gl_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 8; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, gl_sel_cb, popup);
	}
	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 392);
	elm_object_content_set(popup, box);

	evas_object_show(popup);
}

//#define EDJ_FILE "edje/text.edj"
#define EDJ_FILE "edje/combo.edj"

Evas_Object* TizenComboOptionView::createViewItem(Evas_Object *parent){
	DBG("TizenComboOptionView::createViewItem");
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

	elm_object_part_text_set(layout, "caption", _(name().c_str()));

	Evas_Object *label = elm_label_add(layout);
	//Evas_Object *label = elm_button_add(layout);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0.0);

	std::string text = ((ZLStaticTextOptionEntry&)*myOption).initialValue();

	//elm_object_part_text_set(layout, "text", _(text.c_str()));

	elm_label_line_wrap_set(label, ELM_WRAP_MIXED);
	text = "<font_size=30>" + text + "</font_size>";
	elm_object_text_set(label,_(text.c_str()));
	elm_object_part_content_set(layout, "label", label);
	ZLTizenApplicationWindow *tw =  myTab->myTizenOptionsDialog->myWindows;
//	evas_object_smart_callback_add(label, "clicked", list_it_list_cb,tw->win);
	evas_object_event_callback_add(layout, EVAS_CALLBACK_MOUSE_UP, up_callback, tw->win);


/*	check = elm_check_add(layout);
	//elm_object_text_set(check, "Default");
	elm_object_style_set(check, "on&off");
	elm_check_state_set(check, EINA_TRUE);

	elm_object_part_content_set(layout, "check", check);
*/



//	elm_object_text_set(label, _("<align=left><b>TizenBooleanOptionView</b></align>"));



	return layout;
}

void TizenComboOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
}

void TizenComboOptionView::_onAccept() const { }





