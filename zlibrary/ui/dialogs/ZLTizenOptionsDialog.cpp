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

#define ELM_ZLUI_EDJ "/opt/usr/apps/org.tizen.tizen-fbreader/shared/res/ui.edj"

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

static Evas_Object*
create_labels(Evas_Object *parent)
{
	Evas_Object *layout, *label, *label2, *label3, *label4, *label5;

	layout = elm_layout_add(parent);
	if (elm_layout_file_set(layout, ELM_ZLUI_EDJ, "label_layout") == 0) DBG("error set layout ");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	label = elm_label_add(layout);
	elm_object_part_content_set(layout, "label1", label);
	elm_object_text_set(label, _("<align=left>left aligned label</align>"));

	label2 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label2", label2);
	elm_object_text_set(label2, _("<align=center>center aligned label<align>"));

	label3 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label3", label3);
	elm_label_wrap_width_set(label3, 100);
	elm_object_text_set(label3, _("<align=right>right aligned label</align>"));

   label4 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label4", label4);
	elm_label_wrap_width_set(label4, 100);
	elm_object_text_set(label4, _("<align=left>left aligned label</align>"));

	label5 = elm_label_add(layout);
	elm_object_part_content_set(layout, "label5", label5);
	//elm_label_line_wrap_set(label5, EINA_TRUE);
	elm_label_wrap_width_set(label5, 100);
	elm_object_text_set(label5, _("<align=left>label changes line automatically if label wrap width is set and the text length is bigger than the width of the label</align>"));

	return layout;
}

void ZLTizenOptionsDialog::createOptionsDialogObject(Evas_Object *nf){
	DBG("createOptionsDialogObject");
	Evas_Object *scroller, *layout, *label;
//	scroller = create_scroller(nf);
	//elm_naviframe_item_push(nf, "Linebreakmodes", NULL, NULL, scroller, NULL);
//	elm_naviframe_item_push(nf, "Normal Styles", NULL, NULL, scroller, NULL);
	//layout = create_button_view(scroller);

	scroller = create_scroller(nf);
	elm_naviframe_item_push(nf, "Linebreakmodes", NULL, NULL, scroller, NULL);

	layout = create_labels(nf);

	elm_object_content_set(scroller, layout);


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
