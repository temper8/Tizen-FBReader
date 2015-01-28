/*
 * PageTurningOptionsDialog.cpp
 *
 *  Created on: 16.04.2012
 *      Author: Alex
 */

#include "PageTurningOptionsDialog.h"

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


PageTurningOptionsDialog::PageTurningOptionsDialog(): AbstractOptionsDialog(ZLResourceKey("PageTurningOptionsDialog"), true) {
	// TODO Auto-generated constructor stub
	FBReader &fbreader = FBReader::Instance();

	ZLOptionsDialog &dialog = this->dialog();

	ZLDialogContent &scrollingTab = dialog.createTab(ZLResourceKey("Scrolling"));

	scrollingTab.addOption(ZLResourceKey("keyLinesToScroll"), new ZLSimpleSpinOptionEntry(fbreader.LinesToScrollOption, 1));
	scrollingTab.addOption(ZLResourceKey("keyLinesToKeep"), new ZLSimpleSpinOptionEntry(fbreader.LinesToKeepOption, 1));
//	scrollingTab.addOption(ZLResourceKey("keyScrollDelay"), new ZLSimpleSpinOptionEntry(fbreader.KeyScrollingDelayOption, 50));
	const bool hasTouchScreen =
		ZLBooleanOption(ZLCategoryKey::EMPTY, ZLOption::PLATFORM_GROUP, ZLOption::TOUCHSCREEN_PRESENTED, false).value();
	if (hasTouchScreen) {
		ZLToggleBooleanOptionEntry *enableTapScrollingEntry =
			new ZLToggleBooleanOptionEntry(fbreader.EnableTapScrollingOption);
		scrollingTab.addOption(ZLResourceKey("enableTapScrolling"), enableTapScrollingEntry);
		const bool isFingerTapDetectionSupported =
			ZLBooleanOption(ZLCategoryKey::EMPTY, ZLOption::PLATFORM_GROUP, ZLOption::FINGER_TAP_DETECTABLE, false).value();
		if (isFingerTapDetectionSupported) {
			ZLOptionEntry *fingerOnlyEntry =
				new ZLSimpleBooleanOptionEntry(fbreader.TapScrollingOnFingerOnlyOption);
			scrollingTab.addOption(ZLResourceKey("fingerOnly"), fingerOnlyEntry);
			enableTapScrollingEntry->addDependentEntry(fingerOnlyEntry);
			enableTapScrollingEntry->onStateChanged(enableTapScrollingEntry->initialState());
		}

   const bool hasVolumeKeys = ZLBooleanOption(ZLCategoryKey::EMPTY, ZLOption::PLATFORM_GROUP, ZLOption::VOLUME_KEYS_PRESENTED, false).value();

  if (hasVolumeKeys) {
	        ZLToggleBooleanOptionEntry *volumeKeysEntry =
	                new ZLToggleBooleanOptionEntry(fbreader.EnableTapScrollingByVolumeKeysOption);
	        scrollingTab.addOption(ZLResourceKey("volumeKeys"), volumeKeysEntry);
	    }
	}

}

PageTurningOptionsDialog::~PageTurningOptionsDialog() {
	// TODO Auto-generated destructor stub
}
