/*
 * ZLTizenProgressDialog.cpp
 *
 *  Created on: Oct 31, 2016
 *      Author: Alex
 */


#include <unistd.h>

#include <ZLibrary.h>
#include <ZLTimeManager.h>

#include "../ZLTizenApplicationWindow.h"

#include "ZLTizenProgressDialog.h"

#include "ZLTizenDialogManager.h"

#include "ZLTizen.h"
#include "logger.h"

ZLTizenProgressDialog::ZLTizenProgressDialog(ZLTizenApplicationWindow* windows, const ZLResourceKey &key) : ZLProgressDialog(key), myRunnable(NULL), myWindows(windows) {

	DBG("ZLTizenProgressDialog  = %s",messageText().c_str());

/*
	__pProgressPopup  = new Tizen::Ui::Controls::ProgressPopup();
	if (__pProgressPopup) {


			result r;
			//__pProgressPopup = new (std::nothrow) ProgressPopup();

			r = __pProgressPopup->Construct(true, Tizen::Graphics::Dimension(500,300));
			AppLog("r = %d",r);
			r =__pProgressPopup->SetTitleText(messageText().c_str());
			AppLog("r = %d",r);
			r = __pProgressPopup->SetShowState(true);
			AppLog("r = %d",r);
			//r = __pProgressPopup->Show();
			if (r!=0)	{
				delete __pProgressPopup;
				__pProgressPopup = null;
				AppLog("delete __pPopup");
				}
			}

*/
}
static void popup_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = (Evas_Object *)data;
	evas_object_del(popup);
}
static Evas_Object * create_processing_popup(Evas_Object *win)//(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *layout;
	Evas_Object *btn;
	Evas_Object *progressbar;
	//Evas_Object *win = data;
	//Ecore_Timer *timer;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	elm_object_part_text_set(popup, "title,text", "Title");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", popup_btn_clicked_cb, popup);

	/* layout */
	layout = elm_layout_add(popup);

	ZLTizenUtil::layout_edj_set(layout, "fbr.processing_view_layout");
	//elm_layout_file_set(layout, ELM_DEMO_EDJ, "processing_view_layout");

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(layout, "elm.text", "Loading...");

	progressbar = elm_progressbar_add(layout);
	elm_object_style_set(progressbar, "process_medium");
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	elm_object_part_content_set(layout, "processing", progressbar);
	//timer = ecore_timer_add(0.1, progressbar_timer_cb, popup);

	elm_object_content_set(popup, layout);

	evas_object_data_set(popup, "progressbar", progressbar);
	//evas_object_data_set(popup, "timer", timer);
	//evas_object_event_callback_add(popup, EVAS_CALLBACK_DEL, progressbar_popup_del_cb, timer);

	evas_object_show(popup);
	return popup;
}



void ZLTizenProgressDialog::OnProgressPopupCanceled(void)
{
	//__pProgressPopup->SetShowState(false);
	//Invalidate(true);
}
/*
Tizen::Base::Object* ZLbadaProgressDialog::Run(void){
	AppLog("ZLbadaProgressDialog RRRun");

	myRunnable->run();
	theWorkIsDone = true;
	if (showProgress)	__pProgressPopup->EndModal(0);

	AppLog("ZLbadaProgressDialog RRRun end");
	return null;
}
*/
void ZLTizenProgressDialog::run(ZLRunnable &runnable) {
	DBG("ZLTizenProgressDialog run");
	myRunnable = &runnable;
	Evas_Object *win = myWindows->win;
	Evas_Object *popup = create_processing_popup(win);

/*
	if (__pProgressPopup) {
		    __pMonitor = new Monitor;
	    	__pMonitor->Construct();

		    AppLog("ConstructAnimationFrameList");
			theWorkIsDone = false;
			showProgress = false;
			Thread* runTread = new Thread;
			runTread->Construct(*this);
			runTread->Start();
			__pProgressPopup->Construct(false,false);
			__pProgressPopup->SetTitleText(messageText().c_str());
			__pProgressPopup->SetBounds(260,260,200,500);
			__pProgressPopup->AddProgressPopupEventListener(*this);
			__pProgressPopup->SetShowState(true);
			AppLog("Thread Start()");
            if (!theWorkIsDone) {
            	showProgress = true;
    			 __pProgressPopup->DoModal(modalResult);
    			__pProgressPopup->SetShowState(false);
            }

			delete runTread;
			AppLog("delete runTread");
			delete __pMonitor;
			AppLog("delete __pMonitor;");
			delete __pProgressPopup;
			AppLog("delete __pPopup");
	}
	else*/
	{
		runnable.run();
		DBG("ZLTizenProgressDialog end run");
	}
	evas_object_del(popup);
}


void ZLTizenProgressDialog::setMessage(const std::string &message) {
	DBG("ZLTizenProgressDialog setMessage %s", message.c_str());

}


