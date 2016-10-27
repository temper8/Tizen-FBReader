/*
 * ZLTizenOptionsDialog.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#include "ZLTizenOptionsDialog.h"
#include "ZLTizenDialogContent.h"
#include "logger.h"

#include "ZLTreeTitledNode.h"
#include "../ZLTizenApplicationWindow.h"
#include "ZLTizen.h"

#define ELM_ZLUI_EDJ "/opt/usr/apps/org.tizen.tizen-fbreader/shared/res/ui.edj"
//#define EDJ_FBREADER_FILE "edje/fbreader.edj"
#define EDJ_FBREADER_FILE "edje/fbr.edj"

ZLTizenOptionsDialog::~ZLTizenOptionsDialog() {
	// TODO Auto-generated destructor stub
	DBG("delete ZLTizenOptionsDialog");
	myWindows->refreshPage();
	//deleteObjects();
}

ZLTizenOptionsDialog::ZLTizenOptionsDialog(ZLTizenApplicationWindow *windows, const ZLResource &resource, shared_ptr<ZLRunnable> applyAction) :  ZLOptionsDialog(resource, applyAction), myWindows(windows) {//,myMenuView(0){
	DBG("ZLTizenOptionsDialog resource name = %s",resource.name().c_str());
	//result r = E_SUCCESS;
	DBG("ZLTizenOptionsDialog caption() = %s",caption().c_str());
	new_naviframe();
}


static Evas_Object* create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}
void ZLTizenOptionsDialog::new_naviframe(){
	createOptionsDialogObject(myWindows->naviframe);
}

static Eina_Bool TizenOptionsDialog_destuctor_cb(void *data, Elm_Object_Item *it) {
	DBG("OptionsDialog_destuctor_cb");
	ZLTizenOptionsDialog *tg = (ZLTizenOptionsDialog*)data;
	//if (!tg)
	//delete tg;
	tg->myWindows->refreshPage();
//	 elm_naviframe_item_pop(it);
	return EINA_TRUE;//EINA_FALSE;
}

void ZLTizenOptionsDialog::createOptionsDialogObject(Evas_Object *nf){
	DBG("createOptionsDialogObject");
	Evas_Object *layout = ZLTizenUtil::create_layout(myWindows->naviframe, "fbr.optionsdialog");
	Elm_Object_Item *nf_it = elm_naviframe_item_push(myWindows->naviframe, caption().c_str(), NULL, NULL,	layout, NULL);
	elm_naviframe_item_pop_cb_set(nf_it, TizenOptionsDialog_destuctor_cb, this);
	elmObjectsOptionsDialog = nf_it;
	//elmObjectsList.push_back(nf_it);
//	elm_naviframe_item_pop_cb_set(nf_it, tree_dialog_pop_cb, myWindows);

	myScroller = create_scroller(layout);
//	elmObjectsOptionsDialog = elm_naviframe_item_push(nf, caption().c_str(), NULL, NULL, myScroller, NULL);
	elm_object_part_content_set(layout,  "fbr.optionsdialog.sw", myScroller);
	evas_object_show(myScroller);

	myBox = elm_box_add(myScroller);
	evas_object_size_hint_weight_set(myBox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(myBox, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_homogeneous_set(myBox, EINA_FALSE);
	//elm_box_padding_set(myBox, 0, 5 * elm_config_scale_get());
	elm_box_align_set(myBox, 0.0, 0.0);
	evas_object_show(myBox);
	elm_object_content_set(myScroller, myBox);
	//Evas_Object * layout = create_labels(myBox);
	//evas_object_show(layout);
	//elm_box_pack_end(myBox, layout);
}

void ZLTizenOptionsDialog::deleteObjects(){
	DBG("ZLTizenOptionsDialog::deleteObjects");
	elm_object_item_del(elmObjectsOptionsDialog);
}

void ZLTizenOptionsDialog::addEvasViewItem(Evas_Object* viewItem){
	evas_object_show(viewItem);
	elm_box_pack_end(myBox, viewItem);
}

ZLDialogContent &ZLTizenOptionsDialog::createTab(const ZLResourceKey &key){
	DBG("ZLbadaOptionsDialog::createTab = %s",key.Name.c_str());
	ZLTizenDialogContent *tab = new ZLTizenDialogContent(this, tabResource(key));
	//TODO проследить за уничторежнием TABов... чувствую тут проблема возможна
//	myDialogForm->myTabs.push_back(tab);
	return *tab;
}

bool ZLTizenOptionsDialog::run(){

	DBG("ZLTizenOptionsDialog::run()");


	return true;
}

const std::string &ZLTizenOptionsDialog::selectedTabKey() const {
	 DBG("&ZLbadaOptionsDialog::selectedTabKey()");
	 return std::string();
}

void ZLTizenOptionsDialog::selectTab(const ZLResourceKey &key){
	 DBG("&ZLbadaOptionsDialog::selectTab()= %s",key.Name.c_str());
}


void ZLTizenOptionsDialog::apply() {
	ZLOptionsDialog::accept();
}

void ZLTizenOptionsDialog::setMenuEntry(ZLMenuOptionEntry* option){
	DBG("&ZLbadaOptionsDialog::setMenuEntry()");
//	myMenuView = new MenuView(std::string(), std::string(), (ZLMenuOptionEntry*)option, null, 0, 0, 0);
//	myDialogForm->setMenuView(myMenuView);
}

bool ZLTizenOptionsDialog::runInternal(){
	return true;
}
