/*
 * ZLTizen.h
 *
 *  Created on: Oct 12, 2016
 *      Author: Alex
 */

#ifndef ZLTIZEN_H_
#define ZLTIZEN_H_

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#define EDJ_FILE "edje/musicplayerui.edj"



class ZLTizenUtil {

public:
	static void app_get_resource2(const char *edj_file_in, char *edj_path_out, int edj_path_max);

};



#endif /* ZLTIZEN_H_ */
