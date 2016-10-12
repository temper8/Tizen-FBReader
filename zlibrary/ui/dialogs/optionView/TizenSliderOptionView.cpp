/*
 * TizenSliderOptionView.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: alex
 */

#include "TizenSliderOptionView.h"

#include "../ZLTizenOptionsDialog.h"

#include "../ZLTizen.h"
#include "logger.h"

TizenSliderOptionView::TizenSliderOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TizenSliderOptionView %s", name.c_str());

//	 myTab->myTizenOptionsDialog->addEvasViewItem(createTestAlignment(tab->myTizenOptionsDialog->myBox));
}

static void slider_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
//appdata_s *ad = data;
Evas_Object *layout = (Evas_Object *)data;
char buf[5];
double value = elm_slider_value_get(obj);
sprintf(buf, "%d", (int)value);
elm_object_part_text_set(layout, "Value", _(buf));
}

static Evas_Object *create_slider(Evas_Object *parent, Eina_Bool is_center_point)
{
	Evas_Object *slider;

	slider = elm_slider_add(parent);
	elm_slider_indicator_show_set(slider, EINA_TRUE);
	evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(slider, "changed", slider_changed_cb, parent);
	elm_slider_indicator_format_set(slider, "%1.0f");
	if (is_center_point)
		elm_object_style_set(slider, "center_point");

	return slider;
}


Evas_Object* TizenSliderOptionView::createViewItem(Evas_Object *parent){

	Evas_Object * label, *label2;
	Evas_Object *slider;
	Evas_Object *layout = elm_layout_add(parent);

	ZLTizenUtil::layout_edj_set(layout, "fbr.SliderOptionView");

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
