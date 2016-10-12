/*
 * ZLTizen.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: Alex
 */

#include "ZLTizen.h"
#include "logger.h"

void ZLTizenUtil::app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, edj_path_max, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}

void ZLTizenUtil::layout_edj_set(Evas_Object *obj, const char *edj_name){
	char edj_path[PATH_MAX] = {0, };

	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path, (int)PATH_MAX, "%sedje/%s.edj", res_path, edj_name);
		free(res_path);
	}
	DBG("edj_path = %s", edj_path);
	//ZLTizenUtil::app_get_resource(EDJ_FILE, edj_path, (int)PATH_MAX);
	if (elm_layout_file_set(obj, edj_path, edj_name) == 0)
				DBG("error set layout ");

}
