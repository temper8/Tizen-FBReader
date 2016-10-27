/*
 * TizenColorOptionView.cpp
 *
 *  Created on: Oct 22, 2016
 *      Author: Alex
 */


#include "TizenColorOptionView.h"
#include "../ZLTizenOptionsDialog.h"
#include "../../ZLTizenApplicationWindow.h"

#include "../ZLTizen.h"
#include "logger.h"

TizenColorOptionView::TizenColorOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
	 DBG("TestTizenOptioTizenColorOptionViewnView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
}

void TizenColorOptionView::setOptionColor(int r,int g,int b){
	((ZLColorOptionEntry&)*myOption).onAccept(ZLColor((unsigned char) r,(unsigned char)g, (unsigned char)b));
	elm_bg_color_set(bg, r, g, b);
}

static void selected_color_cb(void *data, Evas_Object *obj, void *event_info)
{
   TizenColorOptionView *myOptionView = (TizenColorOptionView *)data;
   int r, g, b, a;
   elm_colorselector_color_get(obj, &r, &g, &b, &a);
   myOptionView->setOptionColor(r,g,b);
   elm_object_item_del(myOptionView->nf_it_colorselector);
}

Evas_Object* TizenColorOptionView::create_colorselector(Evas_Object *parent)
{
	/* add color palette widget */
	Evas_Object *colorselector;
	Elm_Object_Item *it;
	const Eina_List *color_list;

	colorselector = elm_colorselector_add(parent);
	elm_colorselector_mode_set(colorselector, ELM_COLORSELECTOR_BOTH );
	evas_object_size_hint_weight_set(colorselector, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(colorselector, 0, EVAS_HINT_FILL);
	evas_object_show(colorselector);

	color_list = elm_colorselector_palette_items_get(colorselector);
	it = (Elm_Object_Item*)eina_list_nth(color_list, 3);

	evas_object_smart_callback_add(colorselector, "color,item,selected", selected_color_cb, this);

//	elm_object_item_signal_emit(it, "elm,state,selected", "elm");

	return colorselector;
}

Evas_Object* TizenColorOptionView::create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_object_style_set(scroller, "dialogue");
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}


// создание colorselector
static void colorselector_callback(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	DBG("TizenComboOptionView---createViewItem");
	TizenColorOptionView *myOptionView = (TizenColorOptionView *)data;
	ZLTizenApplicationWindow *tw =  myOptionView->myTab->myTizenOptionsDialog->myWindows;

	Evas_Object *colorselector, *scroller, *layout;
	Evas_Object *nf = tw->naviframe;

	scroller = myOptionView->create_scroller(nf);
	layout = elm_layout_add(scroller);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	ZLTizenUtil::layout_edj_set(layout, "fbr.white_bg_layout");

	colorselector = myOptionView->create_colorselector(layout);
	elm_object_part_content_set(layout, "elm.swallow.content", colorselector);
	elm_object_content_set(scroller, layout);


	Elm_Object_Item *nf_it = elm_naviframe_item_push(nf, "Colorselector", NULL, NULL, scroller, NULL);
	myOptionView->nf_it_colorselector = nf_it;

}


Evas_Object* TizenColorOptionView::createViewItem(Evas_Object *parent){

	Evas_Object *layout = elm_layout_add(parent);

	ZLTizenUtil::layout_edj_set(layout, "fbr.ColorOptionView");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);

	bg = elm_bg_add(layout);

	ZLColor сolor = ((ZLColorOptionEntry&)*myOption).color();
	elm_bg_color_set(bg, сolor.Red, сolor.Green, сolor.Blue);

	elm_object_part_content_set(layout, "color", bg);

	elm_object_part_text_set(layout, "caption", _(name().c_str()));

	evas_object_event_callback_add(layout, EVAS_CALLBACK_MOUSE_UP, colorselector_callback, this);

	return layout;
}


void TizenColorOptionView::_createItem() {
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();

}

void TizenColorOptionView::_onAccept() const { }
