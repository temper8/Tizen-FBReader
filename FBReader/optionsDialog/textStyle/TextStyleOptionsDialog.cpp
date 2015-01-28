/*
 * TextStyleOptionsDialog.cpp
 *
 *  Created on: 21.12.2011
 *      Author: Alex
 */

#include "TextStyleOptionsDialog.h"

#include <optionEntries/ZLSimpleOptionEntry.h>
#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>

#include "../../fbreader/FBReader.h"
#include "../../fbreader/FBView.h"
#include "../../options/FBOptions.h"

#include <ZLTextStyle.h>
#include <ZLTextStyleCollection.h>
#include <ZLTextStyleOptions.h>

static const ZLResourceKey KEY_STYLE("style");
static const ZLResourceKey KEY_BASE("Base");

static const ZLResourceKey KEY_BOLD("bold");
static const ZLResourceKey KEY_ITALIC("italic");
static const ZLResourceKey KEY_FONTFAMILY("fontFamily");
static const ZLResourceKey KEY_FONTSIZE("fontSize");
static const ZLResourceKey KEY_FONTSIZEDIFFERENCE("fontSizeDifference");
static const ZLResourceKey KEY_ALLOWHYPHENATIONS("allowHyphenations");
static const ZLResourceKey KEY_AUTOHYPHENATIONS("autoHyphenations");
static const ZLResourceKey KEY_DUMMY("");

static const ZLResourceKey KEY_LINESPACING("lineSpacing");
static const ZLResourceKey KEY_FIRSTLINEINDENT("firstLineIndent");
static const ZLResourceKey KEY_ALIGNMENT("alignment");
static const ZLResourceKey KEY_SPACEBEFORE("spaceBefore");
static const ZLResourceKey KEY_SPACEAFTER("spaceAfter");
static const ZLResourceKey KEY_STARTINDENT("startIndent");
static const ZLResourceKey KEY_ENDINDENT("endIndent");

TextStyleOptionsDialog::TextStyleOptionsDialog(ZLTextStyleDecoration &decoration) : AbstractOptionsDialog(ZLResourceKey("OptionsDialog"), true),  myTextStyleDecoration(decoration)  {
	// TODO Auto-generated constructor stub
	FBReader &fbreader = FBReader::Instance();
	FBOptions &options = FBOptions::Instance();
	ZLOptionsDialog &dialog = this->dialog();
	ZLDialogContent &tabStyles = dialog.createTab(ZLResourceKey("Styles"));

	if (&myTextStyleDecoration != 0) {
		tabStyles.addOption(KEY_FONTFAMILY, new ZLTextFontFamilyWithBaseOptionEntry(myTextStyleDecoration.FontFamilyOption, tabStyles.resource(KEY_FONTFAMILY), *fbreader.context()));

		tabStyles.addOption(KEY_FONTSIZEDIFFERENCE, new ZLSimpleSpinOptionEntry(myTextStyleDecoration.FontSizeDeltaOption, 2));

		tabStyles.addOption(KEY_BOLD, new ZLSimpleBoolean3OptionEntry(myTextStyleDecoration.BoldOption));

		tabStyles.addOption(KEY_ITALIC, new ZLSimpleBoolean3OptionEntry(myTextStyleDecoration.ItalicOption));

		tabStyles.addOption(KEY_ALLOWHYPHENATIONS, new ZLSimpleBoolean3OptionEntry(myTextStyleDecoration.AllowHyphenationsOption));

	}

	ZLTextStyleDecoration *d;
	d = &myTextStyleDecoration;
	if ((d != 0) && (d->isFullDecoration())) {
		ZLTextFullStyleDecoration *decoration = (ZLTextFullStyleDecoration*)d;

		ZLDialogContent &tabFormat = dialog.createTab(ZLResourceKey("Format"));

		tabFormat.addOptions(
					KEY_SPACEBEFORE, new ZLSimpleSpinOptionEntry(decoration->SpaceBeforeOption, 1),
					KEY_STARTINDENT, new ZLSimpleSpinOptionEntry(decoration->LineStartIndentOption, 1)
			);

		tabFormat.addOptions(
			KEY_SPACEAFTER, new ZLSimpleSpinOptionEntry(decoration->SpaceAfterOption, 1),
			KEY_ENDINDENT, new ZLSimpleSpinOptionEntry(decoration->LineEndIndentOption, 1)
			);

		tabFormat.addOptions(
			KEY_LINESPACING, new ZLTextLineSpaceOptionEntry(decoration->LineSpacePercentOption, tabFormat.resource(KEY_LINESPACING), true),
			KEY_FIRSTLINEINDENT, new ZLSimpleSpinOptionEntry(decoration->FirstLineIndentDeltaOption, 1)
			);

		tabFormat.addOptions(
			KEY_ALIGNMENT, new ZLTextAlignmentOptionEntry(decoration->AlignmentOption, tabFormat.resource(KEY_ALIGNMENT), true),
			KEY_DUMMY, 0
		);
	}
}

TextStyleOptionsDialog::~TextStyleOptionsDialog() {
	// TODO Auto-generated destructor stub
}
