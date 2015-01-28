/*
 * AppearanceOptionsDialog.cpp
 *
 *  Created on: 13.04.2012
 *      Author: Alex
 */

#include "AppearanceOptionsDialog.h"

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



class RotationTypeEntry : public ZLComboOptionEntry {

public:
	RotationTypeEntry(const ZLResource &resource, ZLIntegerOption &angleOption);

	const std::string &initialValue() const;
	const std::vector<std::string> &values() const;
	void onAccept(const std::string &value);

private:
	ZLIntegerOption &myAngleOption;
	std::vector<std::string> myValues;
};

RotationTypeEntry::RotationTypeEntry(const ZLResource &resource, ZLIntegerOption &angleOption) : myAngleOption(angleOption) {


	myValues.push_back(resource["portrait"].value());
	myValues.push_back(resource["landscape"].value());
	myValues.push_back(resource["reversePortrait"].value());
	myValues.push_back(resource["reverseLandscape"].value());
	myValues.push_back(resource["sensor"].value());

}

const std::string &RotationTypeEntry::initialValue() const {
	switch (myAngleOption.value()) {
		default:
			return myValues[0];
		case ZLView::DEGREES90:
			return myValues[1];
		case ZLView::DEGREES180:
			return myValues[2];
		case ZLView::DEGREES270:
			return myValues[3];
		case -1:
			return myValues[4];
	}
}

const std::vector<std::string> &RotationTypeEntry::values() const {
	return myValues;
}

void RotationTypeEntry::onAccept(const std::string &value) {
	int angle = ZLView::DEGREES0;
	if (value == myValues[1]) {
		angle = ZLView::DEGREES90;
	} else if (value == myValues[2]) {
		angle = ZLView::DEGREES180;
	} else if (value == myValues[3]) {
		angle = ZLView::DEGREES270;
	} else if (value == myValues[4]) {
		angle = -1;
	}
	myAngleOption.setValue(angle);
}


AppearanceOptionsDialog::AppearanceOptionsDialog()  : AbstractOptionsDialog(ZLResourceKey("AppearanceOptionsDialog"), false) {
	FBReader &fbreader = FBReader::Instance();

	ZLOptionsDialog &dialog = this->dialog();

	ZLDialogContent &rotationTab = dialog.createTab(ZLResourceKey("Rotation"));
	ZLResourceKey directionKey("direction");

	rotationTab.addOption(directionKey, new RotationTypeEntry(rotationTab.resource(directionKey), fbreader.AngleStateOption));
	//rotationTab.addOption(directionKey, new RotationTypeEntry(rotationTab.resource(directionKey), fbreader.RotationAngleOption));

}

AppearanceOptionsDialog::~AppearanceOptionsDialog() {
	// TODO Auto-generated destructor stub
}
