/*
 * OpenFileDialogAction.h
 *
 *  Created on: 24.01.2012
 *      Author: Alex
 */

#ifndef OPENFILEDIALOGACTION_H_
#define OPENFILEDIALOGACTION_H_

#include <ZLResource.h>
#include "ZLRunnable.h"
#include <shared_ptr.h>

class OpenFileDialogAction : public ZLRunnableWithKey  {
public:
	OpenFileDialogAction();
	void run();
	ZLResourceKey key() const;
};



#endif /* OPENFILEDIALOGACTION_H_ */
