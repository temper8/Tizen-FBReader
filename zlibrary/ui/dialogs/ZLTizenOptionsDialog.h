/*
 * ZLTizenOptionsDialog.h
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#ifndef ZLTIZENOPTIONSDIALOG_H_
#define ZLTIZENOPTIONSDIALOG_H_

#include <ZLOptionsDialog.h>

class ZLTizenApplicationWindow;

class ZLTizenOptionsDialog: public ZLOptionsDialog {

public:
	ZLTizenOptionsDialog( ZLTizenApplicationWindow *windows, const ZLResource &resource, shared_ptr<ZLRunnable> applyAction);
	virtual ~ZLTizenOptionsDialog();

public:
	virtual ZLDialogContent &createTab(const ZLResourceKey &key);
	//virtual ZLDialogContent* createTab2(const ZLResourceKey &key);
	virtual bool run();
    virtual void setMenuEntry(ZLMenuOptionEntry* option);
    ZLTizenApplicationWindow *myWindows;
	void apply();

protected:
	virtual const std::string &selectedTabKey() const;
	virtual void selectTab(const ZLResourceKey &key);
	virtual bool runInternal();

};

#endif /* ZLTIZENOPTIONSDIALOG_H_ */
