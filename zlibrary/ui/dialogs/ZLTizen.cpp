/*
 * ZLTizen.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: Alex
 */

#include "ZLTizen.h"


void ZLTizenUtil::app_get_resource2(const char *edj_file_in, char *edj_path_out, int edj_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, edj_path_max, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}
