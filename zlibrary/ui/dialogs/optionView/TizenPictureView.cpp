/*
 * TizenPictureView.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: alex
 */

#include "../ZLTizen.h"
#include "TizenPictureView.h"
#include "../ZLTizenOptionsDialog.h"
#include "../../ZLTizenApplicationWindow.h"
#include "../../ZLTizenViewWidget.h"
#include "logger.h"

TizenPictureView::TizenPictureView(const std::string &name, const std::string &tooltip, ZLPictureOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) :
										ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn),
										myActions(option->myActions) {
	 DBG("TizenPictureView %s", name.c_str());
	 myTab->myTizenOptionsDialog->addEvasViewItem(createViewItem(tab->myTizenOptionsDialog->myBox));
}


static void button_clicked(void *data, Evas_Object *btn, void *ev){
	TizenPictureView* tv = (TizenPictureView*)data;
	tv->myActions[1]->run();
}

void TizenPictureView::createImage(Evas_Object *image_obj){
	if (myImage.isNull())  return;
/*
	shared_ptr<ZLImage> cover = myImage;
	if (cover.isNull()) { DBG("cover.isNull()");}
	else
	{
		shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*cover);
		if (!coverData.isNull()) {
			ZLImageData &image = *coverData;
			Bitmap *tmpBmp = 	((ZLbadaImageData&)image).pBitmap;
			pBmp = makeCover(tmpBmp);
			}
			else
			{	DBG("coverData.isNull()");}

	}
	elm_image_memfile_set(image_obj, const void * 	img,	size_t 	size, NULL,	NULL );
*/

}

Evas_Object* TizenPictureView::createViewItem(Evas_Object *parent){
	Evas_Object *image, *label, *label2;
	Evas_Object *button1, *button2, *button3, *button4;
	Evas_Object *layout = elm_layout_add(parent);

	ZLTizenUtil::layout_edj_set(layout, "fbr.PictureView");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.5);
//-----------------------------------
//	image = elm_image_add(layout);
//	Evas* canvas = evas_object_evas_get(image);
//	Evas_Object *img = evas_object_image_add(canvas);

	//createImage(image);

	Evas* canvas = evas_object_evas_get(layout);

	Evas_Object *img = evas_object_image_add(canvas);

	evas_object_image_colorspace_set(img, EVAS_COLORSPACE_ARGB8888);
	evas_object_size_hint_weight_set(img, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_align_set(img, EVAS_HINT_FILL, EVAS_HINT_FILL);
	myPaintEventHandler = new ZLPaintEventHandler(img);
	elm_object_part_content_set(layout, "picture", img);
	evas_object_show(img);

	//elm_object_part_content_set(layout, "picture", image);
//-------------------------------
	button1 = elm_button_add(layout);
	elm_object_part_content_set(layout, "button1", button1);

	button2 = elm_button_add(layout);
	elm_object_part_content_set(layout, "button2", button2);

	button3 = elm_button_add(layout);
	elm_object_part_content_set(layout, "button3", button3);

	button4 = elm_button_add(layout);
	elm_object_part_content_set(layout, "button4", button4);

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
			case	1:	elm_object_text_set(button1, _(text.c_str()));
						evas_object_smart_callback_add(button1, "clicked", button_clicked, this);
						break;
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
