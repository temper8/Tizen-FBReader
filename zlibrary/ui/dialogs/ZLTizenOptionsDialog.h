/*
 * ZLTizenOptionsDialog.h
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#ifndef ZLTIZENOPTIONSDIALOG_H_
#define ZLTIZENOPTIONSDIALOG_H_

#include <ZLOptionsDialog.h>

#include <Elementary.h>



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
public:
	void new_naviframe();
	void createOptionsDialogObject(Evas_Object *nf);
	void addEvasViewItem(Evas_Object* viewItem);
	Evas_Object *myScroller;
	Evas_Object *myBox;
	Elm_Object_Item* elmObjectsOptionsDialog;
	char edj_path[PATH_MAX] = {0, };
	void deleteObjects();
};

#endif /* ZLTIZENOPTIONSDIALOG_H_ */
