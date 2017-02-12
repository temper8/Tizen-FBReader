/*
 * ZLTizenProgressDialog.h
 *
 *  Created on: Oct 31, 2016
 *      Author: Alex
 */

#ifndef ZLTIZENPROGRESSDIALOG_H_
#define ZLTIZENPROGRESSDIALOG_H_


#include <ZLProgressDialog.h>
#include <ZLRunnable.h>

#include <Elementary.h>
#include "ZLTizen.h"

class ZLTizenApplicationWindow;

class ZLTizenProgressDialog : public ZLProgressDialog {
public:
		ZLTizenProgressDialog(ZLTizenApplicationWindow* windows, const ZLResourceKey &key);

        void run(ZLRunnable &runnable);

		void setMessage(const std::string &message);
		virtual void OnProgressPopupCanceled(void);
private:

		bool theWorkIsDone;
		bool showProgress;
		ZLRunnable* myRunnable;
		ZLTizenApplicationWindow* myWindows;
	 	int   modalResult;
	 	Evas_Object * create_processing_popup(Evas_Object *win);
		void OnStop(void);
};



#endif /* ZLTIZENPROGRESSDIALOG_H_ */
