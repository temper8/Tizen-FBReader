/*
 * ZLTizenDialogContent.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#include "ZLTizenDialogContent.h"
#include "optionView/ZLTizenOptionView.h"
#include "optionView/TestTizenOptionView.h"
#include "logger.h"

ZLTizenDialogContent::	ZLTizenDialogContent(ZLTizenOptionsDialog *dialog, const ZLResource &resource): ZLDialogContent(resource), myTizenOptionsDialog(dialog) {
	// TODO Auto-generated constructor stub

}

ZLTizenDialogContent::~ZLTizenDialogContent() {
	// TODO Auto-generated destructor stub
}

void ZLTizenDialogContent::addOption(const std::string &name, const std::string &tooltip, ZLOptionEntry *option) {
	DBG("addOption %s %s",name.c_str(),tooltip.c_str());
	createViewByEntry(name, tooltip, option, 0, 12);

}

void ZLTizenDialogContent::addOptions(const std::string &name0, const std::string &tooltip0, ZLOptionEntry *option0,
								const std::string &name1, const std::string &tooltip1, ZLOptionEntry *option1) {

	DBG("addOptions0 %s %s",name0.c_str(), tooltip0.c_str());
	DBG("addOptions1 %s %s",name1.c_str(), tooltip1.c_str());
	createViewByEntry(name0, tooltip0, option0, 0, 5);
	createViewByEntry(name1, tooltip1, option1, 7, 12);
}

/*void ZLTizenDialogContent::addItem(DialogForm *form, int row, int fromColumn, int toColumn) {

}*/

void ZLTizenDialogContent::close() {

}


void ZLTizenDialogContent::createViewByEntry(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, int fromColumn, int toColumn) {
	DBG("createViewByEntry ");
	if (option == 0) {
		return;
	}
	ZLTizenOptionView *view = 0;
	DBG("createViewByEntry switch");
/*
	switch (option->kind()) {
		case ZLOptionEntry::BOOLEAN:
			DBG("ZLOptionEntry::BOOLEAN:");
			view = new TizenBooleanOptionView(name, tooltip, (ZLBooleanOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::STATIC:
			DBG("ZLOptionEntry::STATIC:");
			  view = new TizenTextOptionView(name, tooltip, (ZLStaticTextOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
    	case ZLOptionEntry::PICTURE:
		    view = new TizenPictureView(name, tooltip, (ZLPictureOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
		    break;
		case ZLOptionEntry::SPIN:
			DBG("ZLOptionEntry::SPIN:");
			view = new TizenSpinOptionView(name, tooltip, (ZLSpinOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::COMBO:
			DBG("ZLOptionEntry::COMBO:");
			view = new TizenComboOptionView(name, tooltip, (ZLComboOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::COLOR:
			DBG("ZLOptionEntry::COLOR:");
			view = new TizenColorOptionView(name, tooltip, (ZLColorOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
	/*	case ZLOptionEntry::BOOLEAN3:
			AppLog("ZLOptionEntry::BOOLEAN3:");
			view = new Boolean3OptionView(name, tooltip, (ZLBoolean3OptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::STRING:
			AppLog("ZLOptionEntry::STRING:");
			view = new StringOptionView(name, tooltip, (ZLStringOptionEntry*)option, this, false, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::PASSWORD:
			AppLog("ZLOptionEntry::PASSWORD:");
			//view = new StringOptionView(name, tooltip, (ZLStringOptionEntry*)option, this, true, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::CHOICE:
			AppLog("ZLOptionEntry::CHOICE:");
			view = new ChoiceOptionView(name, tooltip, (ZLChoiceOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;



		case ZLOptionEntry::KEY:
			AppLog("ZLOptionEntry::KEY:");
			//view = new KeyOptionView(name, tooltip, (ZLKeyOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::ORDER:
			AppLog("ZLOptionEntry::ORDER:");
			//view = new OrderOptionView(name, tooltip, (ZLOrderOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;


    	case ZLOptionEntry::BUTTON:
    		AppLog("ZLOptionEntry::BUTTON");
    		    view = new ButtonView(name, tooltip, (ZLButtonOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
    		    break;
    	case ZLOptionEntry::MENU:
    		AppLog("ZLOptionEntry::MENU");
    		    view = new MenuView(name, tooltip, (ZLMenuOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
    		    break;	*/
/*	}
*/
	if (view == 0) view = new TestTizenOptionView(name, tooltip, option, this, myRowCounter, fromColumn, toColumn);

	if (view != 0) {
		view->setVisible(option->isVisible());
		addView(view);
	}
}
