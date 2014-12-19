/*
 * ZLTizenLibraryImplementation.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#include "logger.h"

#include "ZLTizenLibraryImplementation.h"
#include "ZLTizenPaintContext.h"

ZLTizenLibraryImplementation::ZLTizenLibraryImplementation() {
	// TODO Auto-generated constructor stub

}

ZLTizenLibraryImplementation::~ZLTizenLibraryImplementation() {
	// TODO Auto-generated destructor stub
}

void ZLibraryImplementation::initLibrary() {
	new ZLTizenLibraryImplementation();
}

static int my_argc;
static char **my_argv;

void ZLTizenLibraryImplementation::init(int &argc, char **&argv){
	my_argc = argc;
	my_argv = argv;
}

ZLTizenApplicationWindow *ZLTizenLibraryImplementation::myWindow = NULL;

bool ZLTizenLibraryImplementation::app_create(void *data){
	DBG("ZLTiLibImp-app_create");
	ZLApplication *app = (ZLApplication*)data;
	myWindow = new ZLTizenApplicationWindow(app);
	myWindow->init();
	app->createApplication();

	return true;
}


void ZLTizenLibraryImplementation::app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

void ZLTizenLibraryImplementation::app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

void ZLTizenLibraryImplementation::app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

void ZLTizenLibraryImplementation::app_terminate(void *data)
{
	/* Release all resources. */
}


void ZLTizenLibraryImplementation::ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

void ZLTizenLibraryImplementation::ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

void ZLTizenLibraryImplementation::ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

void ZLTizenLibraryImplementation::ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

void ZLTizenLibraryImplementation::ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}



void ZLTizenLibraryImplementation::run(ZLApplication *application) {
	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = ZLTizenLibraryImplementation::app_create;
	event_callback.terminate = ZLTizenLibraryImplementation::app_terminate;
	event_callback.pause = ZLTizenLibraryImplementation::app_pause;
	event_callback.resume = ZLTizenLibraryImplementation::app_resume;
	event_callback.app_control = ZLTizenLibraryImplementation::app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ZLTizenLibraryImplementation::ui_app_low_battery, application);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ZLTizenLibraryImplementation::ui_app_low_memory, application);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ZLTizenLibraryImplementation::ui_app_orient_changed, application);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ZLTizenLibraryImplementation::ui_app_lang_changed, application);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ZLTizenLibraryImplementation::ui_app_region_changed, application);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	int ret = ui_app_main(my_argc, my_argv, &event_callback, application);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

}


ZLPaintContext *ZLTizenLibraryImplementation::createContext(){
	return new ZLTizenPaintContext();
}
