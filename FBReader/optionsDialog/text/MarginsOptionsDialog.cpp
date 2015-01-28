/*
 * MarginsOptionsDialog.cpp
 *
 *  Created on: 13.04.2012
 *      Author: Alex
 */

#include "MarginsOptionsDialog.h"

#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>

#include <optionEntries/ZLSimpleOptionEntry.h>
#include <optionEntries/ZLToggleBooleanOptionEntry.h>
#include <optionEntries/ZLFontFamilyOptionEntry.h>

#include <ZLTextStyleCollection.h>
#include <ZLTextStyleOptions.h>

#include "../../fbreader/FBReader.h"
#include "../../fbreader/FBView.h"
#include "../../options/FBOptions.h"
#include "../../options/FBTextStyle.h"

MarginsOptionsDialog::MarginsOptionsDialog(): AbstractOptionsDialog(ZLResourceKey("MarginsOptionsDialog"), true) {
	// TODO Auto-generated constructor stub
	FBReader &fbreader = FBReader::Instance();
	FBOptions &options = FBOptions::Instance();

	ZLOptionsDialog &dialog = this->dialog();

	ZLDialogContent &marginTab = dialog.createTab(ZLResourceKey("Margins"));
	marginTab.addOptions(
		ZLResourceKey("left"), new ZLSimpleSpinOptionEntry(options.LeftMarginOption, 1),
		ZLResourceKey("right"), new ZLSimpleSpinOptionEntry(options.RightMarginOption, 1)
	);
	marginTab.addOptions(
		ZLResourceKey("top"), new ZLSimpleSpinOptionEntry(options.TopMarginOption, 1),
		ZLResourceKey("bottom"), new ZLSimpleSpinOptionEntry(options.BottomMarginOption, 1)
	);

}

MarginsOptionsDialog::~MarginsOptionsDialog() {
	// TODO Auto-generated destructor stub
}
