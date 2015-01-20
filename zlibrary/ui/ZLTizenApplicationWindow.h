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

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "tizen-fbreader"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.tizen-fbreader"
#endif

#include "ZLApplicationWindow.h"

class ZLTizenApplicationWindow : public ZLApplicationWindow {
public:
	ZLTizenApplicationWindow(ZLApplication *application);
	virtual ~ZLTizenApplicationWindow();

	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
	Evas_Object *naviframe;

	static void win_back_cb(void *data, Evas_Object *obj, void *event_info);

protected:
	virtual ZLViewWidget *createViewWidget();

private:
	void initToolbar(ToolbarType type);

protected:
	// TODO: change to pure virtual
	virtual void initMenu() {};
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

	//virtual void close() = 0;

	void setCaption(const std::string &caption) {};

	//virtual void grabAllKeys(bool grab) = 0;

	//virtual void setFullscreen(bool fullscreen) = 0;
	//virtual bool isFullscreen() const = 0;

	// TODO: change to pure virtual (?)
	//virtual void setHyperlinkCursor(bool) {}

	void setVisualParameter(const std::string &id, const std::string &value) {};
	void setParameterValueList(const std::string &id, const std::vector<std::string> &values) {};
	const std::string &visualParameter(const std::string &id) {return "test";};


};

#endif /* ZLTIZENAPPLICATIONWINDOW_H_ */
