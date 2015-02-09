/*
 * ZLTizenOptionsDialog.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#include "ZLTizenOptionsDialog.h"
#include "ZLTizenDialogContent.h"
#include "logger.h"


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


ZLDialogContent &ZLTizenOptionsDialog::createTab(const ZLResourceKey &key){
	DBG("ZLbadaOptionsDialog::createTab = %s",key.Name.c_str());
	//ZLTizenDialogContent tab;// = new ZLTizenDialogContent(myDialogForm, tabResource(key));
	//TODO проследить за уничторежнием TABов... чувствую тут проблема возможна
//	myDialogForm->myTabs.push_back(tab);
//	return NULL;
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
