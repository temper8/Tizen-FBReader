/*
 * OpenFileDialogAction.cpp
 *
 *  Created on: 24.01.2012
 *      Author: Alex
 */

#include "OpenFileDialogAction.h"
#include <ZLDialogManager.h>

OpenFileDialogAction::OpenFileDialogAction() {
	// TODO Auto-generated constructor stub

}

void OpenFileDialogAction::run() {
//	ZLDialogManager::Instance().startOpenFileDialog();
	//if (ReadingOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	//}
}

ZLResourceKey OpenFileDialogAction::key() const {
	return ZLResourceKey("OpenFileDialog");
}


