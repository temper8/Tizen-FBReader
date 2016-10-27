/*
 * ZLTizenApplicationWindow.h
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#ifndef ZLTIZENAPPLICATIONWINDOW_H_
#define ZLTIZENAPPLICATIONWINDOW_H_

#include <string>
#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#include "../../core/src/application/ZLMenu.h"

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "tizen-fbreader"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.tizen-fbreader"
#endif

#include "ZLApplicationWindow.h"

class ZLTreeDialog;
class ZLOptionsDialog;
class ZLRunnable;
class ZLTizenViewWidget;
class ZLTizenTreeDialog;

class ZLTizenApplicationWindow : public ZLApplicationWindow {
public:
	ZLTizenApplicationWindow(ZLApplication *application);
	virtual ~ZLTizenApplicationWindow();

	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
	Evas_Object *naviframe;
	Evas_Object *popup;
	Evas_Object *drawer_panel;
	Evas_Object *menuList;


	static void win_back_cb(void *data, Evas_Object *obj, void *event_info);
	Evas_Object * createDrawerPanel(Evas_Object *parent);
	static void onMenuItemSelected(void *data, Evas_Object *obj, void *event_info);

	void AddMenuItem(const std::string &name, const  std::string &id);
	void gotoPrevPage();
	void gotoNextPage();
	void mouseDown(int x, int y);
	void refreshPage();

	void createTestDialog();
	shared_ptr<ZLTreeDialog> createTizenTreeDialog(const ZLResource &resource);
	shared_ptr<ZLOptionsDialog> createTizenOptionsDialog(const ZLResource &resource, shared_ptr<ZLRunnable> applyAction);
	shared_ptr<ZLTreeDialog> myTreeDialog;
	shared_ptr<ZLOptionsDialog> myOptionsDialog;
	ZLTizenViewWidget* myTizenViewWidget;
	void deleteOptionsDialog();
	void deleteTreeDialog();

protected:
	virtual ZLViewWidget *createViewWidget();

private:
	void initToolbar(ToolbarType type);

protected:
	class MenuBuilder : public ZLMenuVisitor {

	public:
		MenuBuilder(ZLTizenApplicationWindow &window);

	private:
		void processSubmenuBeforeItems(ZLMenubar::Submenu &submenu);
		void processSubmenuAfterItems(ZLMenubar::Submenu &submenu);
		void processItem(ZLMenubar::PlainItem &item);
		void processSepartor(ZLMenubar::Separator &separator);

	private:
		ZLTizenApplicationWindow &myWindow;
	};
	// TODO: change to pure virtual
	virtual void initMenu();
/*
	ToolbarType type(const ZLToolbar::Item &item) const;
	bool hasFullscreenToolbar() const;
	void onButtonPress(const ZLToolbar::AbstractButtonItem &button);
	virtual void addToolbarItem(ZLToolbar::ItemPtr item) = 0;
	*/
	// TODO: change to pure virtual
//	virtual void setToolbarItemState(ZLToolbar::ItemPtr /*item*/, bool /*visible*/, bool /*enabled*/) {};
//	virtual void setToggleButtonState(const ZLToolbar::ToggleButtonItem &toggleButton) = 0;

	virtual void refresh() {};
	virtual void processAllEvents() {};

protected:
	// TODO: change to pure virtual
	virtual void present() {}

	virtual void close();

	void setCaption(const std::string &caption) {};

	//virtual void grabAllKeys(bool grab) = 0;

	//virtual void setFullscreen(bool fullscreen) = 0;
	//virtual bool isFullscreen() const = 0;

	// TODO: change to pure virtual (?)
	//virtual void setHyperlinkCursor(bool) {}


	void setVisualParameter(const std::string &id, const std::string &value) {};
	void setParameterValueList(const std::string &id, const std::vector<std::string> &values) {};
	const std::string &visualParameter(const std::string &id) {return "test";};

	friend class MenuBuilder;
};

#endif /* ZLTIZENAPPLICATIONWINDOW_H_ */
