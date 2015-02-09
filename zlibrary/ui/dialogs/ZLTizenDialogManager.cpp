/*
 * ZLTizenDialogManager.cpp
 *
 *  Created on: Feb 8, 2015
 *      Author: alex
 */

#include "ZLTizenDialogManager.h"
#include "logger.h"
#include "../ZLTizenApplicationWindow.h"
//#include "../view/badaForm.h"
#include "../ZLTizenViewWidget.h"
#include "ZLTizenDialog.h"
//#include "ZLbadaOpenFileDialog.h"
#include "ZLTizenOptionsDialog.h"
#include "ZLTizenTreeDialog.h"
#include "ZLTypeId.h"

ZLTizenDialogManager::ZLTizenDialogManager() {
	// TODO Auto-generated constructor stub

}

ZLTizenDialogManager::~ZLTizenDialogManager() {
	// TODO Auto-generated destructor stub
}

shared_ptr<ZLDialog> ZLTizenDialogManager::createDialog(const ZLResourceKey &key) const {
	DBG("ZLTizenDialogManager::createDialog");
	return new ZLTizenDialog(resource()[key]);
}



void ZLTizenDialogManager::createApplicationWindow(ZLApplication *application) const {
//	myApplicationWindow = new ZLbadaApplicationWindow(application);
}


shared_ptr<ZLOptionsDialog> ZLTizenDialogManager::createOptionsDialog(const ZLResourceKey &key, shared_ptr<ZLRunnable> applyAction) const {
	DBG("ZLbadaDialogManager::createOptionsDialog");
	//ZLbadaOptionsDialog* b= new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
	//mybadaOptionsDialog =new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
	shared_ptr<ZLOptionsDialog> b = new ZLTizenOptionsDialog(myApplicationWindow, resource()[key], applyAction);

//	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
//	TizenDialogForm* d = (TizenDialogForm*)pFrame->GetCurrentForm();
//	d->__badaOptionsDialog = b;


	//b->myDialogForm = myApplicationWindow->viewWidget().mybadaForm->CreateDalogForm();
	return b;//new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
}



void ZLTizenDialogManager::informationBox(const std::string &title, const std::string &message) const {

/*	MessageBox messageBox;
	messageBox.Construct(title.c_str(), message.c_str(), MSGBOX_STYLE_NONE , 2000);

	// Calls ShowAndWait - draw, show itself and process events
	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);
*/
}

void ZLTizenDialogManager::errorBox(const ZLResourceKey &key, const std::string &message) const {
/*	QMessageBox::critical(
		qApp->mainWidget(),
		::qtString(dialogTitle(key)),
		::qtString(message),
		::qtButtonName(OK_BUTTON)
	);*/
}

int ZLTizenDialogManager::questionBox(const ZLResourceKey &key, const std::string &message, const ZLResourceKey &button0, const ZLResourceKey &button1, const ZLResourceKey &button2) const {
	DBG("ZLbadaDialogManager::questionBox");
/*
	MessageBox messageBox;
	messageBox.Construct(dialogTitle(key).c_str(), message.c_str(), MSGBOX_STYLE_YESNO, 0);

	// Calls ShowAndWait - draw, show itself and process events
	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);
    AppLog("modalResult %d", modalResult);
    int r;
	switch(modalResult)
	   {
	    case MSGBOX_RESULT_YES:
	    	AppLog("modalResult Yes");
	    	r = 0;
	        break;

	    case MSGBOX_RESULT_CANCEL:
		   	AppLog("modalResult Cancel");
		    r = 1;
		    break;

	    default:
	    	r = 1;
	        break;
	    }
	AppLog("r %d", r);

	return r;
			/*
			QMessageBox::question(
		qApp->mainWidget(),
		::qtString(dialogTitle(key)),
		::qtString(message),
		::qtButtonName(button0),
		::qtButtonName(button1),
		::qtButtonName(button2)
	);*/
}

shared_ptr<ZLProgressDialog> ZLTizenDialogManager::createProgressDialog(const ZLResourceKey &key) const {
	return NULL;//new ZLbadaProgressDialog(key);
}






shared_ptr<ZLTreeDialog> ZLTizenDialogManager::createTreeDialog(const ZLResourceKey &key) const {
	DBG("ZLbadaDialogManager::createTreeDialog");

	//myTreeDialog = new ZLbadaTreeDialog(resource()[key]);
	//return myTreeDialog;

	shared_ptr<ZLTreeDialog> b = (ZLTreeDialog*) new ZLTizenTreeDialog(resource()[key]);
	//Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	//TreeViewForm* d = (TreeViewForm*)pFrame->GetCurrentForm();
	//d->__myTreeDialog = b;
   return b;

}

//shared_ptr<ZLTreeDialog> ZLbadaDialogManager::myTreeDialog = 0;

void 	ZLTizenDialogManager::deleteTreeDialog(){
	//delete myTreeDialog;
	//myTreeDialog = 0;
}

shared_ptr<ZLDialogContent> ZLTizenDialogManager::createContent(const ZLResourceKey &key) const {
	DBG("ZLbadaDialogManager::createTreeDialog");
	//return new ZLbadaDialogContent(resource()[key]);
}

