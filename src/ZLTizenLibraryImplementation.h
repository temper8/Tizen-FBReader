/*
 * ZLTizenLibraryImplementation.h
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#ifndef ZLTIZENLIBRARYIMPLEMENTATION_H_
#define ZLTIZENLIBRARYIMPLEMENTATION_H_

#include "ZLibraryImplementation.h"
#include "ZLTizenApplicationWindow.h"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.tizen-fbreader"
#endif

class ZLTizenLibraryImplementation : public ZLibraryImplementation  {
public:
	ZLTizenLibraryImplementation();
	virtual ~ZLTizenLibraryImplementation();



	void init(int &argc, char **&argv);
	ZLPaintContext *createContext();
	void run(ZLApplication *application);

	static ZLTizenApplicationWindow *myWindow;

	static bool	app_create(void *data);
	static void	app_control(app_control_h app_control, void *data);
	static void app_pause(void *data);
	static void app_resume(void *data);
	static void app_terminate(void *data);

	static void	ui_app_lang_changed(app_event_info_h event_info, void *user_data);
	static void	ui_app_orient_changed(app_event_info_h event_info, void *user_data);
	static void	ui_app_region_changed(app_event_info_h event_info, void *user_data);
	static void	ui_app_low_battery(app_event_info_h event_info, void *user_data);
	static void	ui_app_low_memory(app_event_info_h event_info, void *user_data);

};

#endif /* ZLTIZENLIBRARYIMPLEMENTATION_H_ */
