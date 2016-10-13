/*
 * TizenComboOptionView.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: Alex
 */


#include "TizenComboOptionView.h"
#include "../ZLTizenOptionsDialog.h"
#include "../../ZLTizenApplicationWindow.h"

#include "ZLOptionEntry.h"

#include "../ZLTizen.h"
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

static char* gl_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	char *text = (char*) data;
	return strdup(text);
}

static char*
gl_radio_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	if (!strcmp(part,"elm.text"))
	{
		const std::vector<std::string> *values = (std::vector<std::string> *)evas_object_data_get(obj, "values");
		int index = (int) data;
		return strdup((*values)[index].c_str());
	}
	else return NULL;
}

static Evas_Object* gl_radio_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int index = (int) data;
	Elm_Object_Item *it = elm_genlist_nth_item_get(obj, index);
	DBG("gl_radio_content_get_cb %d", index);
	DBG("gl_radio_content_get_cb part %s", part);
	if (!strcmp(part, "elm.swallow.end")) {
		Evas_Object *radio;
		Evas_Object *radio_main = (Evas_Object *)evas_object_data_get(obj, "radio");
		radio = elm_radio_add(obj);
		elm_radio_group_add(radio, radio_main);
		elm_radio_state_value_set(radio, index + 1);
		if (index == 1) elm_radio_value_set(radio, 1);
		evas_object_size_hint_weight_set(radio, EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(radio, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_propagate_events_set(radio, EINA_FALSE);
		elm_atspi_accessible_relationship_append(it, ELM_ATSPI_RELATION_DESCRIBED_BY, radio);
		elm_atspi_accessible_relationship_append(radio, ELM_ATSPI_RELATION_CONTROLLED_BY, it);
		return radio;
	}
	return NULL;
}

// обработчик выбора элемента списока
static void gl_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = (Elm_Object_Item *)event_info;
	int index = (int) data;
	Evas_Object *radio;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	radio = elm_object_item_part_content_get(it, "elm.swallow.end");
	elm_radio_value_set(radio, index + 1);

	Evas_Object *popup = (Evas_Object *)evas_object_data_get(obj, "popup");
	evas_object_del(popup);
}


// создание popup содержащим genlist с radio
static void up_callback(void *data, Evas *e, Evas_Object *obj, void *event_info)
//static void list_it_list_cb(void *data, Evas_Object *obj, void *event_info)
{
	DBG("TizenComboOptionView---createViewItem");
	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *box;
	Evas_Object *genlist;
	Evas_Object *radio;

	int i;
	//Evas_Object *win = (Evas_Object *)data;
	TizenComboOptionView *myCombo = (TizenComboOptionView *)data;
	ZLTizenApplicationWindow *tw =  myCombo->myTab->myTizenOptionsDialog->myWindows;
	Evas_Object *win = tw->win;
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	elm_object_part_text_set(popup, "title,text", _(myCombo->name().c_str()));
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);


	layout = elm_layout_add(popup);
	ZLTizenUtil::layout_edj_set(layout, "fbr.RadioList");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(popup, layout);

	/* box */
	box = elm_box_add(layout);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* genlist */
	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	/* radio */
	radio = elm_radio_add(genlist);
	elm_radio_state_value_set(radio, 0);
	elm_radio_value_set(radio, 0);
	evas_object_data_set(genlist, "radio", radio);

	itc.item_style = "default";
	itc.func.text_get = gl_radio_text_get_cb;
	itc.func.content_get = gl_radio_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	//for (i = 0; i < 8; i++) {
//		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, gl_sel_cb, popup);
//	}

	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*myCombo->option();
	const std::vector<std::string> &values = comboOption.values();
	const std::string &initial = comboOption.initialValue();

	evas_object_data_set(genlist, "values", (const void *)&values);
	int selectedIndex = -1;
	int index = 0;

	evas_object_data_set(genlist, "popup", popup);

	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it, ++index) {

			elm_genlist_item_append(genlist, &itc, (void *) index, NULL, ELM_GENLIST_ITEM_NONE, gl_sel_cb, (void *) index);
			//__pComboList->AddItem(&itemText, null, null, null );
			if (*it == initial) {
				selectedIndex = index;
			}
		}
	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);

	evas_object_size_hint_min_set(box, -1, 492);
//	elm_object_content_set(popup, box);
	elm_object_part_content_set(layout,  "fbr.RadioList.sw", box);
	evas_object_show(popup);
}


Evas_Object* TizenComboOptionView::createViewItem(Evas_Object *parent){
	DBG("TizenComboOptionView::createViewItem");

	Evas_Object *layout = elm_layout_add(parent);

	ZLTizenUtil::layout_edj_set(layout, "fbr.ComboOptionView");

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
//	ZLTizenApplicationWindow *tw =  myTab->myTizenOptionsDialog->myWindows;
//	evas_object_smart_callback_add(label, "clicked", list_it_list_cb,tw->win);
	evas_object_event_callback_add(layout, EVAS_CALLBACK_MOUSE_UP, up_callback, this);

	return layout;
}

void TizenComboOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
}

void TizenComboOptionView::_onAccept() const { }





