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


class ZLTizenProgressDialog : public ZLProgressDialog
						//	 public Tizen::Base::Runtime::IRunnable,
						//	 Tizen::Ui::IProgressPopupEventListener
							 {
public:
		ZLTizenProgressDialog(const ZLResourceKey &key);

        void run(ZLRunnable &runnable);
               // void run(TreeActionListener* listener); // for wait dialog while loading book

		void setMessage(const std::string &message);
		//IProgressPopupEventListener
		virtual void OnProgressPopupCanceled(void);
private:

		bool theWorkIsDone;
		bool showProgress;
		ZLRunnable* myRunnable;

	//    Tizen::Ui::Controls::ProgressPopup*			__pProgressPopup;
	 	int   modalResult;
	// 	Tizen::Base::Runtime::Monitor*        __pMonitor;

		void OnStop(void);
	//	Tizen::Base::Object* Run(void);
};



#endif /* ZLTIZENPROGRESSDIALOG_H_ */
