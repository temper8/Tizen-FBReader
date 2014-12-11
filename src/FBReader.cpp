
#include "FBReader.h"

FBReader::FBReader(const std::string &bookToOpen): ZLApplication(bookToOpen)  {

}

FBReader::~FBReader() {

}


bool FBReader::createApplication(){
	/* Window */
	ZLApplication::createApplication();


return true;
}

bool FBReader::app_create(void *data){
	FBReader *f = (FBReader*)data;
	f->createApplication();
	return true;
}


void FBReader::app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

void FBReader::app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

void FBReader::app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

void FBReader::app_terminate(void *data)
{
	/* Release all resources. */
}




void FBReader::ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

void FBReader::ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

void FBReader::ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

void FBReader::ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

void FBReader::ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

