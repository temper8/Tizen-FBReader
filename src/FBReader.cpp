
#include "FBReader.h"

FBReader::FBReader(const std::string &bookToOpen) : win(NULL), conform(NULL), label(NULL) {

}

FBReader::~FBReader() {

}

static void
win_delete_request_cb(void *data , Evas_Object *obj , void *event_info)
{
	ui_app_exit();
}

void FBReader::win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	FBReader *f = (FBReader*)data;
	/* Let window go to hide state. */
	elm_win_lower(f->win);
}

bool FBReader::createApplication(){
	/* Window */
	win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(win, EEXT_CALLBACK_BACK, FBReader::win_back_cb, this);

	/* Conformant */
	conform = elm_conformant_add(win);
	elm_win_indicator_mode_set(win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	evas_object_show(conform);

	/* Label*/
	label = elm_label_add(conform);
	elm_object_text_set(label, "Hello EFL and FBReader!");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(conform, label);
	evas_object_show(label);

	/* Show window after base gui is set up */
	evas_object_show(win);
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

