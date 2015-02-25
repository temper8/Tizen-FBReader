/*
 * ZLTizenDialogManager.h
 *
 *  Created on: Feb 8, 2015
 *      Author: alex
 */

#ifndef ZLTIZENDIALOGMANAGER_H_
#define ZLTIZENDIALOGMANAGER_H_

#include <ZLDialogManager.h>

class ZLApplication;
class ZLTizenApplicationWindow;
class ZLTizenOptionsDialog;

class ZLTizenDialogManager : public ZLDialogManager {

public:
	static void createInstance() { ourInstance = new ZLTizenDialogManager(); }
	//static ZLTizenDialogManager* tizenInstance();
private:
	ZLTizenDialogManager();
	virtual ~ZLTizenDialogManager();
public:
	ZLApplicationWindow* createApplicationWindow(ZLApplication *application) const ;

	shared_ptr<ZLDialog> createDialog(const ZLResourceKey &key) const;
	shared_ptr<ZLOptionsDialog> createOptionsDialog(const ZLResourceKey &key, shared_ptr<ZLRunnable> applyAction) const;
//	shared_ptr<ZLOpenFileDialog> createOpenFileDialog(const ZLResourceKey &key, const std::string &directoryPath, const std::string &filePath, const ZLOpenFileDialog::Filter &filter) const;
//	void startOpenFileDialog() const;
	virtual void deleteOptionsDialog();
	virtual void deleteTreeDialog();

	shared_ptr<ZLTreeDialog> createTreeDialog(const ZLResourceKey &key) const;
	shared_ptr<ZLDialogContent> createContent(const ZLResourceKey &key) const;

	void informationBox(const std::string &title, const std::string &message) const;
	void errorBox(const ZLResourceKey &key, const std::string &message) const;
	int questionBox(const ZLResourceKey &key, const std::string &message, const ZLResourceKey &button0, const ZLResourceKey &button1, const ZLResourceKey &button2) const;
	shared_ptr<ZLProgressDialog> createProgressDialog(const ZLResourceKey &key) const;

	bool isClipboardSupported(ClipboardType type) const { return false; }
	void setClipboardText(const std::string &text, ClipboardType type) const {}
	void setClipboardImage(const ZLImageData &imageData, ClipboardType type) const {}
private:
	mutable ZLTizenApplicationWindow *myApplicationWindow;
	static shared_ptr<ZLTreeDialog> myTreeDialog;
	mutable shared_ptr<ZLOptionsDialog> myTizenOptionsDialog;
	//mutable ZLOptionsDialog* mybadaOptionsDialog;
};
#endif /* ZLTIZENDIALOGMANAGER_H_ */
