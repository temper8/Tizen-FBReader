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

ZLTizenOptionsDialog::~ZLTizenOptionsDialog() {
	// TODO Auto-generated destructor stub
}

ZLTizenOptionsDialog::ZLTizenOptionsDialog(ZLTizenApplicationWindow *windows, const ZLResource &resource, shared_ptr<ZLRunnable> applyAction) :  ZLOptionsDialog(resource, applyAction), myWindows(windows) {//,myMenuView(0){
	DBG("ZLTizenOptionsDialog resource name = %s",resource.name().c_str());
	//result r = E_SUCCESS;
	DBG("ZLTizenOptionsDialog caption() = %s",caption().c_str());

//	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
//	myDialogForm = new TizenDialogForm;

	//myDialogForm->showApplyButton = true;
	//myDialogForm->__badaOptionsDialog = this;
//	myDialogForm->Initialize(caption().c_str(),true);

//	myDialogForm->SetPreviousForm(pFrame->GetCurrentForm());
//	r = pFrame->AddControl(*myDialogForm);
//	r = pFrame->SetCurrentForm(*myDialogForm);

}
static Evas_Object* create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}
void ZLTizenOptionsDialog::createOptionsDialogObject(Evas_Object *nf){
	DBG("createOptionsDialogObject");
	Evas_Object *scroller, *layout;

	scroller = create_scroller(nf);
	//layout = create_button_view(scroller);

	Evas_Object *btn, *img, *box;

	box = elm_box_add(scroller);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, 0, 5 * elm_config_scale_get());
	evas_object_show(box);

	/* icon_reorder style */
	btn = elm_button_add(box);
	elm_object_style_set(btn, "icon_reorder");
	//evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)1);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);
	/* icon_expand_add style */
	btn = elm_button_add(box);
	elm_object_style_set(btn, "icon_expand_add");
	//evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, (void *)2);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	elm_object_content_set(scroller, box);

	elm_naviframe_item_push(nf, "Normal Styles", NULL, NULL, scroller, NULL);
}

ZLDialogContent &ZLTizenOptionsDialog::createTab(const ZLResourceKey &key){
	DBG("ZLbadaOptionsDialog::createTab = %s",key.Name.c_str());
	ZLTizenDialogContent *tab = new ZLTizenDialogContent(this, tabResource(key));
	//TODO проследить за уничторежнием TABов... чувствую тут проблема возможна
//	myDialogForm->myTabs.push_back(tab);
	return *tab;
}
/*
ZLDialogContent* createTab2(const ZLResourceKey &key){
	ZLTizenDialogContent* tab;
	return (ZLDialogContent*)tab;
}
*/
bool ZLTizenOptionsDialog::run(){

	DBG("ZLTizenOptionsDialog::run()");
//	myDialogForm->Update();
//	myDialogForm->Invalidate(false);

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
