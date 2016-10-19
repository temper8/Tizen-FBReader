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
	TizenSliderOptionView* myTizenSlider = (TizenSliderOptionView*)data;
	Evas_Object *layout = myTizenSlider->layout;

	double value = elm_slider_value_get(obj);

	char cap[50] = {0, };
	snprintf(cap, 50,  "%s : %d",_(myTizenSlider->myCaption.c_str()), (int)value);
	elm_object_part_text_set(layout, "Caption", cap);

}

static Evas_Object *create_slider(Evas_Object *parent, Eina_Bool is_center_point)
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


Evas_Object* TizenSliderOptionView::createViewItem(Evas_Object *parent){

	layout = elm_layout_add(parent);

	ZLTizenUtil::layout_edj_set(layout, "fbr.SliderOptionView");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND,  0.0);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);
	char cap[50] = {0, };
	snprintf(cap, 50,  "%s : %d",_(myCaption.c_str()), ((ZLSpinOptionEntry&)*myOption).initialValue());
	elm_object_part_text_set(layout, "Caption", cap);

	char buf[5] = {0, };
	snprintf(buf, 5, "%d", minValue);
	elm_object_part_text_set(layout, "minValue", _(buf));

	snprintf(buf, 5, "%d", maxValue);
	elm_object_part_text_set(layout, "maxValue", _(buf));

	Evas_Object * slider = create_slider(layout, EINA_FALSE);
	evas_object_smart_callback_add(slider, "changed", slider_changed_cb, this);
	elm_object_part_content_set(layout, "Slider", slider);
	elm_slider_horizontal_set(slider, EINA_TRUE);
	elm_slider_min_max_set(slider, minValue, maxValue);
	elm_slider_value_set(slider, ((ZLSpinOptionEntry&)*myOption).initialValue());
	evas_object_show(slider);
	elm_object_content_set(layout,slider);

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
