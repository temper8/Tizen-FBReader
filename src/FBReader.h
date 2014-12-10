/*
 * FBReader.h
 *
 *  Created on: Dec 8, 2014
 *      Author: Alex
 */

#ifndef FBREADER_H_
#define FBREADER_H_

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

class FBReader {
public:
	FBReader(const std::string &bookToOpen);
	~FBReader();

	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;

	bool createApplication();

	static bool	app_create(void *data);
	static void	app_control(app_control_h app_control, void *data);
	static void app_pause(void *data);
	static void app_resume(void *data);
	static void app_terminate(void *data);

	static void win_back_cb(void *data, Evas_Object *obj, void *event_info);

	static void	ui_app_lang_changed(app_event_info_h event_info, void *user_data);
	static void	ui_app_orient_changed(app_event_info_h event_info, void *user_data);
	static void	ui_app_region_changed(app_event_info_h event_info, void *user_data);
	static void	ui_app_low_battery(app_event_info_h event_info, void *user_data);
	static void	ui_app_low_memory(app_event_info_h event_info, void *user_data);


};



#endif /* FBREADER_H_ */
