

#include "ZLibrary.h"
#include "Fbreader.h"

#include "ZLibraryImplementation.h"


bool ZLibrary::init(int &argc, char **&argv) {


	ZLibraryImplementation::initLibrary();

	if (ZLibraryImplementation::Instance == 0) {
		return false;
	}

	ZLibraryImplementation::Instance->init(argc, argv);
	return true;
}

//ZLPaintContext *ZLibrary::createContext() {
//	return ZLibraryImplementation::Instance->createContext();
//}

void ZLibrary::run(ZLApplication *application) {
	ZLibraryImplementation::Instance->run(application);
}
/*
void ZLibrary::run(FBReader *fbr) {

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = FBReader::app_create;
	event_callback.terminate = FBReader::app_terminate;
	event_callback.pause = FBReader::app_pause;
	event_callback.resume = FBReader::app_resume;
	event_callback.app_control = FBReader::app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, FBReader::ui_app_low_battery, fbr);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, FBReader::ui_app_low_memory, fbr);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, FBReader::ui_app_orient_changed, fbr);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, FBReader::ui_app_lang_changed, fbr);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, FBReader::ui_app_region_changed, fbr);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	int ret = ui_app_main(my_argc, my_argv, &event_callback, fbr);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

}
*/
void ZLibrary::shutdown() {

}
