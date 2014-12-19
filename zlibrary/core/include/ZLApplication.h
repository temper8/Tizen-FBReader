/*
 * ZLApplication.h
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#ifndef ZLAPPLICATION_H_
#define ZLAPPLICATION_H_

#include <string>
#include "shared_ptr.h"

class ZLApplicationWindow;
class ZLViewWidget;
class ZLPaintContext;
class ZLView;

class ZLApplicationBase {

protected:
	ZLApplicationBase(const std::string &name);
	~ZLApplicationBase();
};

class ZLApplication : public ZLApplicationBase {

protected:
	ZLApplication(const std::string &name);
	virtual ~ZLApplication();

public:
	static ZLApplication &Instance();
	static void deleteInstance();


	virtual bool createApplication();

	shared_ptr<ZLPaintContext> context();
	void initWindow();
	void refreshWindow();
	void setView(shared_ptr<ZLView> view);
private:
	static ZLApplication *ourInstance;

private:
	shared_ptr<ZLViewWidget> myViewWidget;
	shared_ptr<ZLView> myInitialView;
//	std::map<std::string,shared_ptr<Action> > myActionMap;
//	mutable shared_ptr<ZLToolbar> myToolbar;
//	mutable shared_ptr<ZLToolbar> myFullscreenToolbar;
//	mutable shared_ptr<ZLMenubar> myMenubar;
	shared_ptr<ZLPaintContext> myContext;
	shared_ptr <ZLApplicationWindow> myWindow;
//	ZLTime myLastKeyActionTime;
//	shared_ptr<ZLMessageHandler> myPresentWindowHandler;

friend class ZLApplicationWindow;
friend class ZLMenuVisitor;
};



#endif /* ZLAPPLICATION_H_ */
