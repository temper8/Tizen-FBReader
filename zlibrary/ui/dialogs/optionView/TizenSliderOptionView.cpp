/*
 * TizenSliderOptionView.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: alex
 */

#include "TizenSliderOptionView.h"

#include "../ZLTizenOptionsDialog.h"

#include "logger.h"

#define EDJ_FILE "/opt/usr/apps/org.tizen.tizen-fbreader/res/edje/alignment.edj"

TizenSliderOptionView::TizenSliderOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TizenSliderOptionView %s", name.c_str());

//	 myTab->myTizenOptionsDialog->addEvasViewItem(createTestAlignment(tab->myTizenOptionsDialog->myBox));
}

static Evas_Object
*create_slider(Evas_Object *parent, Eina_Bool is_center_point)
{
	Evas_Object *slider;

	slider = elm_slider_add(parent);
	elm_slider_indicator_show_set(slider, EINA_TRUE);
	evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_slider_indicator_format_set(slider, "%1.0f");
	if (is_center_point)
		elm_object_style_set(slider, "center_point");

	return slider;
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
#define EDJ_FILE "edje/sliderOptionView_layout.edj"

Evas_Object* TizenSliderOptionView::createViewItem(Evas_Object *parent){

	char edj_path[PATH_MAX] = {0, };

	Evas_Object * label, *label2;
	Evas_Object *slider;
	Evas_Object *layout = elm_layout_add(parent);

//	if (elm_layout_file_set(layout, myTab->myTizenOptionsDialog->edj_path, "test_layout") == 0)
//			DBG("error set layout ");
	app_get_resource(EDJ_FILE, edj_path, (int)PATH_MAX);
	if (elm_layout_file_set(layout, edj_path, "sliderOptionView") == 0)
				DBG("error set layout ");


//	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND,  0.0);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);

	elm_object_part_text_set(layout, "Caption", _(myCaption.c_str()));

	char value[5] = {0, };
	snprintf(value, 5, "%d", ((ZLSpinOptionEntry&)*myOption).initialValue());
	elm_object_part_text_set(layout, "Value", _(value));


//	label = elm_label_add(layout);
////	evas_object_size_hint_align_set(label, 0.0, 0.5);
//	elm_object_part_content_set(layout, "title", label);
//	elm_object_text_set(label, _(myCaption.c_str()));
//	elm_object_content_set(layout,label);
//	//elm_box_pack_end(main_box, label);
//	evas_object_show(label);

	slider = create_slider(layout, EINA_FALSE);
	elm_object_part_content_set(layout, "Slider", slider);
	elm_slider_horizontal_set(slider, EINA_TRUE);
	elm_slider_min_max_set(slider, minValue, maxValue);
	elm_slider_value_set(slider, ((ZLSpinOptionEntry&)*myOption).initialValue());
	evas_object_show(slider);
	elm_object_content_set(layout,slider);
//	elm_box_pack_end(main_box, slider);


	return layout;
}

void TizenSliderOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
	 minValue = ((ZLSpinOptionEntry&)*myOption).minValue();
	 maxValue = ((ZLSpinOptionEntry&)*myOption).maxValue();
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(myTab->myTizenOptionsDialog->myBox));
}

void TizenSliderOptionView::_onAccept() const { }
