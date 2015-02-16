/*
 * TizenPictureView.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: alex
 */

#include "TizenPictureView.h"
#include "../ZLTizenOptionsDialog.h"

#include "logger.h"

TizenPictureView::TizenPictureView(const std::string &name, const std::string &tooltip, ZLPictureOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn),
										myActions(option->myActions) {
	 DBG("TizenPictureView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
}

Evas_Object* TizenPictureView::createViewItem(Evas_Object *parent){
	Evas_Object *image, *label, *label2;
	Evas_Object *button1, *button2, *button3, *button4;
	Evas_Object *layout = elm_layout_add(parent);

	if (elm_layout_file_set(layout, myTab->myTizenOptionsDialog->edj_path, "picture_layout") == 0)
			DBG("error set layout ");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	//evas_object_resize(layout, 400, 400);
	evas_object_size_hint_aspect_set(layout, EVAS_ASPECT_CONTROL_BOTH, 200, 200);

	image = elm_image_add(layout);
	elm_object_part_content_set(layout, "picture", image);
	//evas_object_move(label, 1, 1);
	//evas_object_resize(label, 300, 45);
//	elm_object_text_set(label, _("<align=left><b>TizenPictureView</b></align>"));
//	evas_object_show(label);

	button1 = elm_button_add(layout);
	elm_object_part_content_set(layout, "button1", button1);
//	elm_object_text_set(button1, _(name().c_str()));

	button2 = elm_button_add(layout);
	elm_object_part_content_set(layout, "button2", button2);
//	elm_object_text_set(button2, _(name().c_str()));

	button3 = elm_button_add(layout);
	elm_object_part_content_set(layout, "button3", button3);
//	elm_object_text_set(button3, _(name().c_str()));

	button4 = elm_button_add(layout);
	elm_object_part_content_set(layout, "button4", button4);
//	elm_object_text_set(button4, _(name().c_str()));
//	elm_object_content_set(layout,label2);
//	evas_object_show(label);

	int actionsCount = myActions.size();
	DBG("actionsCount %d", actionsCount);

	actionsCount = myActions.size();
	DBG("after init actionsCount %d", actionsCount);
	actionsCount =0;
	for (int i =1; i<myActions.size();i++){
		shared_ptr<ZLRunnableWithKey> a = myActions[i];
		if (a->makesSense()&&(actionsCount<4)) { DBG("makesSense true %d",actionsCount);
			//myBottonActions[actionsCount++]->SetAction(a);
			std::string text = a->text(ZLResource::resource("networkView")["bookNode"]);
			switch (i){
			case	1:	elm_object_text_set(button1, _(text.c_str())); break;
			case	2:	elm_object_text_set(button2, _(text.c_str())); break;
			case	3:	elm_object_text_set(button3, _(text.c_str())); break;
			case	4:	elm_object_text_set(button3, _(text.c_str())); break;
			}
		}
		else DBG("makesSense false");
	}


	return layout;
}

void TizenPictureView::_createItem() {
//	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 DBG("_createItem %s", name().c_str());
	 myCaption = ZLOptionView::name();
}

void TizenPictureView::_onAccept() const { }