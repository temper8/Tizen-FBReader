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

#include "ZLApplication.h"

class FBReader : public ZLApplication {
public:
	FBReader(const std::string &bookToOpen);
	~FBReader();

	bool createApplication();

	void initWindow();
	void refreshWindow();
	shared_ptr<ZLView> myBookTextView;
};



#endif /* FBREADER_H_ */
