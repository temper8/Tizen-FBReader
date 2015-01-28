/*
 * Copyright (C) 2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>

#include <optionEntries/ZLSimpleOptionEntry.h>
#include <optionEntries/ZLToggleBooleanOptionEntry.h>

#include "ReadingOptionsDialog.h"

#include "../../fbreader/FBReader.h"
#include "../../fbreader/FBView.h"




//ReadingOptionsDialog::ReadingOptionsDialog() : AbstractOptionsDialog(ZLResourceKey("ReadingOptionsDialog"), true) {
ReadingOptionsDialog::ReadingOptionsDialog() : AbstractOptionsDialog(ZLResourceKey("OptionsDialog"), true) {
	FBReader &fbreader = FBReader::Instance();

	ZLOptionsDialog &dialog = this->dialog();

	ZLDialogContent &scrollingTab = dialog.createTab(ZLResourceKey("Scrolling"));
	scrollingTab.addOption(ZLResourceKey("keyLinesToScroll"), new ZLSimpleSpinOptionEntry(fbreader.LinesToScrollOption, 1));
	scrollingTab.addOption(ZLResourceKey("keyLinesToKeep"), new ZLSimpleSpinOptionEntry(fbreader.LinesToKeepOption, 1));
	scrollingTab.addOption(ZLResourceKey("keyScrollDelay"), new ZLSimpleSpinOptionEntry(fbreader.KeyScrollingDelayOption, 50));
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
	}

	ZLDialogContent &selectionTab = dialog.createTab(ZLResourceKey("Selection"));
	selectionTab.addOption(ZLResourceKey("enableSelection"), FBView::selectionOption());

	createIndicatorTab();

//	ZLDialogContent &rotationTab = dialog.createTab(ZLResourceKey("Rotation"));
// ZLResourceKey directionKey("direction");
//	rotationTab.addOption(directionKey, new RotationTypeEntry(rotationTab.resource(directionKey), fbreader.RotationAngleOption));

	createKeyBindingsTab();
}
