/*
 * TizenSpinnerOptionView.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: alex
 */

#include "TizenSpinnerOptionView.h"

#include "../ZLTizenOptionsDialog.h"

#include "logger.h"

#define EDJ_FILE "/opt/usr/apps/org.tizen.tizen-fbreader/res/edje/alignment.edj"

TizenSpinnerOptionView::TizenSpinnerOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TizenSliderOptionView %s", name.c_str());

//	 myTab->myTizenOptionsDialog->addEvasViewItem(createTestAlignment(tab->myTizenOptionsDialog->myBox));
}

Evas_Object* TizenSpinnerOptionView::createTestAlignment(Evas_Object *parent){
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

static Evas_Object
*create_scroller(Evas_Object* parent)
{
	Evas_Object* scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

static Evas_Object
*create_box(Evas_Object *parent, Eina_Bool hor)
{
	Evas_Object *box;
	box = elm_box_add(parent);
	elm_box_horizontal_set(box, hor);
	if (hor) {
		evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	} else {
		evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.0);
		evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.0);
	}
	evas_object_show(box);

	return box;
}

Evas_Object* TizenSpinnerOptionView::createViewItem(Evas_Object *parent){
	Evas_Object * label, *label2;
	Evas_Object *sp;
	Evas_Object *layout = elm_layout_add(parent);

//old	if (elm_layout_file_set(layout, myTab->myTizenOptionsDialog->edj_path, "spinner_layout") == 0)
	DBG("error set layout ");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);


	label = elm_label_add(layout);
	evas_object_size_hint_align_set(label, 0.0, 1.0);
	elm_object_part_content_set(layout, "title", label);
	std::string titleText = "<font_size=40>" + myCaption + "</font_size>";
	elm_object_text_set(label, _(titleText.c_str()));
	elm_object_content_set(layout,label);
	//elm_box_pack_end(main_box, label);
	evas_object_show(label);

	sp = elm_spinner_add(layout);
	evas_object_size_hint_align_set(sp, EVAS_HINT_FILL, -1.0);
	evas_object_size_hint_weight_set(sp, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(layout, "text_string", sp);

	evas_object_show(sp);
	elm_object_content_set(layout,sp);
//	elm_box_pack_end(main_box, slider);


	return layout;
}

void TizenSpinnerOptionView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
	 minValue = ((ZLSpinOptionEntry&)*myOption).minValue();
	 maxValue = ((ZLSpinOptionEntry&)*myOption).maxValue();
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(myTab->myTizenOptionsDialog->myBox));
}

void TizenSpinnerOptionView::_onAccept() const { }
