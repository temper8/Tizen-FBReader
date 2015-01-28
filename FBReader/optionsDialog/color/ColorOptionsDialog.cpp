/*
 * ColorOptionsDialog.cpp
 *
 *  Created on: 21.12.2011
 *      Author: Alex
 */

#include "ColorOptionsDialog.h"

#include <optionEntries/ZLSimpleOptionEntry.h>
#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>

#include "../../fbreader/FBReader.h"
#include "../../fbreader/FBView.h"
#include "../../options/FBOptions.h"

ColorOptionsDialog::ColorOptionsDialog() : AbstractOptionsDialog(ZLResourceKey("ColorOptionsDialog"), true)  {
	// TODO Auto-generated constructor stub
	FBOptions &options = FBOptions::Instance();
	ZLOptionsDialog &dialog = this->dialog();
	ZLDialogContent &colorsTab = dialog.createTab(ZLResourceKey("Colors"));
	ZLResourceKey colorKey("colorFor");
	const ZLResource &resource = colorsTab.resource(colorKey);

	colorsTab.addOption(resource["background"].value(),"",new ZLSimpleColorOptionEntry(options.colorOption("background")));
	colorsTab.addOption(resource["text"].value(),"",new ZLSimpleColorOptionEntry(options.colorOption("text")));
//	colorsTab.addOption(resource["selectionBackground"].value(),"",new ZLSimpleColorOptionEntry(options.colorOption(ZLTextStyle::SELECTION_BACKGROUND)));
	colorsTab.addOption(resource["internalLink"].value(),"", new ZLSimpleColorOptionEntry(options.colorOption("internal")));
	colorsTab.addOption(resource["externalLink"].value(),"", new ZLSimpleColorOptionEntry(options.colorOption("external")));
	colorsTab.addOption(resource["bookLink"].value(),"", new ZLSimpleColorOptionEntry(options.colorOption("book")));
	colorsTab.addOption(resource["highlighted"].value(),"",new ZLSimpleColorOptionEntry( options.colorOption(ZLTextStyle::HIGHLIGHTED_TEXT)));
	colorsTab.addOption(resource["treeLines"].value(),"", new ZLSimpleColorOptionEntry(options.colorOption(ZLTextStyle::TREE_LINES)));
	colorsTab.addOption(resource["indicator"].value(),"", new ZLSimpleColorOptionEntry((FBView::commonIndicatorInfo().ColorOption)));

}

ColorOptionsDialog::~ColorOptionsDialog() {
	// TODO Auto-generated destructor stub
}
