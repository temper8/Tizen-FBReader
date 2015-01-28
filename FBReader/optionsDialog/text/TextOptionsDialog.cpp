/*
 * TextOptionsDialog.cpp
 *
 *  Created on: 07.04.2012
 *      Author: Alex
 */

#include "TextOptionsDialog.h"

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

static const ZLResourceKey _KEY_LINESPACING("lineSpacing");
static const ZLResourceKey _KEY_ALIGNMENT("alignment");

TextOptionsDialog::TextOptionsDialog() : AbstractOptionsDialog(ZLResourceKey("TextOptionsDialog"), true) {
	FBReader &fbreader = FBReader::Instance();
	FBOptions &options = FBOptions::Instance();

	ZLOptionsDialog &dialog = this->dialog();

	FBTextStyle &baseStyle = FBTextStyle::Instance();
	ZLTextStyleCollection &collection = ZLTextStyleCollection::Instance();

	ZLDialogContent &FormatOptionsTab = dialog.createTab(ZLResourceKey("Format"));

	FormatOptionsTab.addOption(ZLResourceKey(_KEY_LINESPACING), new ZLTextLineSpaceOptionEntry(baseStyle.LineSpacePercentOption,  FormatOptionsTab.resource(_KEY_LINESPACING), false));

	FormatOptionsTab.addOption(ZLResourceKey(_KEY_ALIGNMENT), new ZLTextAlignmentOptionEntry(baseStyle.AlignmentOption,FormatOptionsTab.resource(_KEY_ALIGNMENT), false));

	ZLDialogContent &StyleOptionsTab = dialog.createTab(ZLResourceKey("Styles"));

	StyleOptionsTab.addOption(ZLResourceKey("fontFamily"), new ZLFontFamilyOptionEntry(baseStyle.FontFamilyOption, *fbreader.context()));
	StyleOptionsTab.addOption(ZLResourceKey("fontSize"), new ZLSimpleSpinOptionEntry(baseStyle.FontSizeOption, 2));
	StyleOptionsTab.addOption(ZLResourceKey("bold"),new ZLSimpleBooleanOptionEntry(baseStyle.BoldOption));
	StyleOptionsTab.addOption(ZLResourceKey("italic"),new ZLSimpleBooleanOptionEntry(baseStyle.ItalicOption));
	StyleOptionsTab.addOption(ZLResourceKey("autoHyphenations"), new ZLSimpleBooleanOptionEntry(collection.AutoHyphenationOption));

}

TextOptionsDialog::~TextOptionsDialog() {
	// TODO Auto-generated destructor stub
}
