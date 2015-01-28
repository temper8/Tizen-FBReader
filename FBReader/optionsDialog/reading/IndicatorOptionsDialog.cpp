/*
 * IndicatorOptionsDialog.cpp
 *
 *  Created on: 13.04.2012
 *      Author: Alex
 */

#include "IndicatorOptionsDialog.h"

#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>

#include <optionEntries/ZLSimpleOptionEntry.h>
#include <optionEntries/ZLToggleBooleanOptionEntry.h>

#include "../../fbreader/FBReader.h"
#include "../../fbreader/FBView.h"


IndicatorOptionsDialog::IndicatorOptionsDialog(): AbstractOptionsDialog(ZLResourceKey("IndicatorOptionsDialog"), true) {
	FBReader &fbreader = FBReader::Instance();

	ZLOptionsDialog &dialog = this->dialog();

	createIndicatorTab();

}

IndicatorOptionsDialog::~IndicatorOptionsDialog() {
	// TODO Auto-generated destructor stub
}
